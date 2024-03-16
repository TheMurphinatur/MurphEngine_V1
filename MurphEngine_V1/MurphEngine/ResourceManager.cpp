#include "ResourceManager.h"

#include <thread>

#include "Logging.h"
#include "TextData.h"
#include "Bleach_New/BleachNew.h"

MurphEngine::ResourceManager::ResourceManager(ISystem* pSystem)
    : m_pSystem(pSystem)
    , m_pTextureManager(this)
    , m_TextManager(this)
{
}

void MurphEngine::ResourceManager::Initialize()
{
    m_resourceLoaderThread = std::thread(&ResourceManager::ThreadedTextLoaderFunction, this);
}

void MurphEngine::ResourceManager::ShutDown()
{
    m_ShutDownThreadedFunction = true;
    // let the thread know an important atomic_bool was updated.
    NotifyThread();
    m_resourceLoaderThread.join();

    while (!m_loadedQueuePair.empty())
    {
        BLEACH_DELETE(m_loadedQueuePair.front().second);
        m_loadedQueuePair.pop();
    }
}

void MurphEngine::ResourceManager::UpdateThreadedFunction()
{
    std::pair<std::string, ResourceMetaData*> resource;

    m_loadedPairMutex.lock();
    if (!m_loadedQueuePair.empty())
    {
        resource = m_loadedQueuePair.front();
        m_loadedQueuePair.pop();
    }
    m_loadedPairMutex.unlock();

    // if the string reference has data
    if (!resource.first.empty())
    {
        m_TextManager.AddFileToMap(resource);
    }
}

/**
 * \brief updates the threaded function.
 */
void MurphEngine::ResourceManager::UpdateMainFunction()
{
    UpdateThreadedFunction();
}

SDL_Texture* MurphEngine::ResourceManager::GetImage(const char* filepath)
{
    return m_pTextureManager.GetOrLoadImage(filepath);
}

std::string* MurphEngine::ResourceManager::GetText(const std::string& filepath)
{
    return m_TextManager.GetText(filepath);
}

void MurphEngine::ResourceManager::CacheText(const std::string& filepath)
{
    if (!m_TextManager.IsFileLoaded(filepath))
    {
        const std::string localCacheString("Caching " + filepath + ".");
        Log::LogToConsole(localCacheString.c_str());
        AddToQueueAndNotifyThread(filepath);

        return;
    }
    Log::LogToConsole("Text already loaded. Check for double Cache() calls.");
}

/**
 * \brief Return boolean indicating whether file reference was able to be added
 * \param filepath file path of file
 * \return true if reference added, false if file is not loaded
 */
bool MurphEngine::ResourceManager::AddTextReference(const std::string& filepath)
{
    if(m_TextManager.IsFileLoaded(filepath))
    {
        m_TextManager.GetMetaData(filepath)->IncrementRefCount();
        return true;
    }
    return false;
}

void MurphEngine::ResourceManager::RemoveTextReference(const std::string& filepath)
{
    m_TextManager.RemoveReference(filepath);
}

/**
 * \brief Find if file was loaded to cache yet.
 * \param filepath file path
 * \return true if file is loaded into cache
 */
bool MurphEngine::ResourceManager::IsTextRefAvailable(const std::string& filepath)
{
    return m_TextManager.IsFileLoaded(filepath);
}

void MurphEngine::ResourceManager::AddToQueueAndNotifyThread(const std::string& filepath)
{
    // check to avoid adding duplicate references.
    if (m_TextManager.IsFileLoaded(filepath))
    {
        Log::LogToConsole("File already cached.");
        return;
    }

    m_requestPairMutex.lock();
    m_requestQueuePair.emplace( filepath, BLEACH_NEW(TextData));// make a pair of filepath, and new textData for the metadata.
    m_requestPairMutex.unlock();

    NotifyThread();
}

void MurphEngine::ResourceManager::ThreadedTextLoaderFunction()
{
    while (!m_ShutDownThreadedFunction)
    {
        std::unique_lock lock(m_requestPairMutex);
        m_threadCondition.wait(lock, [this]() {return !m_requestQueuePair.empty() || m_ShutDownThreadedFunction == true; });

        std::pair<std::string, ResourceMetaData*> resourcePair;
        //grab the front of queue, and pop.
        if (!m_requestQueuePair.empty())
        {
            resourcePair = m_requestQueuePair.front();
            m_requestQueuePair.pop();
        }
        lock.unlock();

        // load file from request queue value that was popped.
        if (!resourcePair.first.empty())
        {
            std::ifstream file(resourcePair.first, std::ios::in);
            if (!file.is_open())
            {
                auto localOut = std::string{ "Error accessing: " + resourcePair.first + " filepath. Check filepath for validity." };
                Log::LogToConsole(localOut.c_str());
                // we have dead metadata if there is an error. this will clean up the leftover TextData* data.
                BLEACH_DELETE(resourcePair.second);
            }
            else
            {
                // effective STL
                const std::string textFromFile((std::istreambuf_iterator(file)), std::istreambuf_iterator<char>());
                file.close();

                resourcePair.second->SetCacheStatus(kCaching);
                static_cast<TextData*>(resourcePair.second)->SetTextData(textFromFile);

                // lock the loaded mutex, and push the resourcePair from request queue to load queue
                m_loadedPairMutex.lock();
                m_loadedQueuePair.emplace(resourcePair);
                m_loadedPairMutex.unlock();
            }
        }
    }
}


