#include "TextManager.h"

#include <filesystem>
#include <iostream>

#include "TextData.h"
#include "Logging.h"
#include "ResourceMetaData.h"
#include "Bleach_New/BleachNew.h"


MurphEngine::TextManager::TextManager(ResourceManager* pResourceManager)
    : DataManagerBase(pResourceManager)
{
}

MurphEngine::TextManager::~TextManager()
{
    if (!m_loadedData.empty())
    {
        for (const auto& [key, pTextData] : m_loadedData)
        {
            BLEACH_DELETE(pTextData);
        }

        m_loadedData.clear();
    }
}

/**
 * \brief Add filepath and data to map (TODO:maybe remove pair, and make string?)
 * \param dataPair data to be added to map.
 * \return metadata from asset   
 */
MurphEngine::ResourceMetaData* MurphEngine::TextManager::AddFileToMap(std::pair<std::string, ResourceMetaData*> dataPair)
{
    auto localOut = std::string{ "adding " + dataPair.first + " reference." };

    //dataPair.second->IncrementRefCount();
    
    const auto [iterator, success] = m_loadedData.emplace(dataPair.first, dataPair.second);

    if (!success)
    {
        Log::LogToFile("Text Insertion into map failed!");
        BLEACH_DELETE(dataPair.second);
        return nullptr;
    }
    iterator->second->SetCacheStatus(kCached);
    Log::LogToFile("Text Loaded into cache.");

    return iterator->second;
}

/**
 * \brief Get Text From loadedData using filepath as key.
 * \param filepath requested textfile path
 * \return text from map reference.
 */
std::string* MurphEngine::TextManager::GetText(const std::string& filepath)
{
    if (m_loadedData.find(filepath) == m_loadedData.end())
    {
        return nullptr;
    }

    ResourceMetaData* data = m_loadedData.at(filepath);

    if (data->GetCacheStatus() != kCached)
    {
        Log::LogToFile("File was not Cached. Check Removal of references or Add a reference.");
        return nullptr;
    }
    
    //data->IncrementRefCount(); //this may throw of numbers later on. we shall see.
    
    return static_cast<TextData*>(data)->GetText();
}

void MurphEngine::TextManager::RemoveFileFromMap(const std::string& filepath)
{
    const auto localOut = std::string{ "Removing " + filepath + " from map. Reference count was 0" };
    Log::LogToConsole(localOut.c_str());
    BLEACH_DELETE(m_loadedData.at(filepath));
    m_loadedData.erase(filepath);
}

void MurphEngine::TextManager::RemoveReference(const std::string& filepath)
{
    auto localOut = std::string{ "Removing reference to: " + filepath + "." };
    Log::LogToConsole(localOut.c_str());
    const auto& referenceFromMap = m_loadedData.at(filepath);
    referenceFromMap->DecrementRefCount();

    if (referenceFromMap->GetRefCount() <= 0)
    {
        RemoveFileFromMap(filepath);
    }
}

MurphEngine::ResourceMetaData* MurphEngine::TextManager::GetMetaData(const std::string& filepath)
{
    if (m_loadedData.find(filepath) == m_loadedData.end())
    {
        return nullptr;
    }
    return m_loadedData.at(filepath);
}
