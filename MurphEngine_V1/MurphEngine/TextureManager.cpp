#include "TextureManager.h"
#include "ISystem.h"
#include "ResourceManager.h"
#include "TextureData.h"
#include "ResourceMetaData.h"


#include <SDL_image.h>

#include "Bleach_New/BleachNew.h"


MurphEngine::TextureManager::TextureManager(ResourceManager* pManager)
    : m_pResourceManager(pManager)
{
}

MurphEngine::TextureManager::~TextureManager()
{
    if (m_loadedTexturesWithMetaData.empty())
    {
        Log::LogToFile("Map Clear Fail. Texture Map was empty.");
        return;
    }

    for (const auto& [key, pTextureData] : m_loadedTexturesWithMetaData)
    {
        pTextureData->ClearTexture();
        BLEACH_DELETE(pTextureData);
    }

    m_loadedTexturesWithMetaData.clear();
}

bool MurphEngine::TextureManager::IsFileLoaded(const char* filepath)
{
    if (auto search = m_loadedTexturesWithMetaData.find(filepath); search != m_loadedTexturesWithMetaData.end())
        return true;
    else
        return false;
}

/**
 * \brief Add file to Map. (will not add duplicate file paths)
 * \param filepath image filepath
 * \return SDL_Texture* of image at filepath
 */
SDL_Texture* MurphEngine::TextureManager::AddFileToMap(const char* filepath)
{
    SDL_Texture* loadedTexture = m_pResourceManager->GetSystem()->GetGraphics()->LoadTexture(filepath);

    // this is new so i can pass the data by reference and contain the metadata into a pointer.
        //this is leaking memory. track it down.
    auto pLocalData = BLEACH_NEW(TextureData());
    pLocalData->SetTexture(loadedTexture);
    pLocalData->IncrementRefCount();
    pLocalData->SetCacheStatus(kCaching);

    const auto [iterator2, success2] = m_loadedTexturesWithMetaData.emplace(filepath, pLocalData);

    if(!success2)
    {
        Log::LogToFile("Image Insertion into map failed!");
        return nullptr;
    }
    Log::LogToFile("Image Loaded INTO map.");

    return iterator2->second->GetTexture();
}

/**
 * \brief Get image from filepath.
 * \param filepath Image file path
 * \return SDL_Texture* for requested file.
 */
SDL_Texture* MurphEngine::TextureManager::GetOrLoadImage(const char* filepath)
{
    // lock map
    if (IsFileLoaded(filepath))
    {
        auto& data = m_loadedTexturesWithMetaData.at(filepath);

        if (data->GetCacheStatus() == kCached)
        {
            Log::LogToFile("Loading cached Image from Map.");
        }

        //data->IncrementRefCount();
        return data->GetTexture();
    }
    
    return AddFileToMap(filepath);
}

