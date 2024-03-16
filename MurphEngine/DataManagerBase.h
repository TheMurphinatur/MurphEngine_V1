#pragma once
#include <mutex>
#include <string>
#include <unordered_map>

namespace MurphEngine
{
    class ResourceManager;
    class ResourceMetaData;


    class DataManagerBase
    {
    protected:
        ResourceManager* m_pResourceManager;

        std::unordered_map<std::string, ResourceMetaData*> m_loadedData;

    public:
        DataManagerBase(ResourceManager* pResourceManager);
        virtual ~DataManagerBase() = default;

        virtual ResourceMetaData* AddFileToMap(std::pair<std::string, ResourceMetaData*> dataPair) = 0;
        virtual ResourceMetaData* GetMetaData(const std::string& filepath) = 0;
        virtual void RemoveFileFromMap(const std::string& filepath) = 0;
        virtual std::string* GetText(const std::string& filepath) = 0;
        virtual void RemoveReference(const std::string& filepath) = 0;

        bool IsFileLoaded(std::string filepath);
    protected:
    };


}
