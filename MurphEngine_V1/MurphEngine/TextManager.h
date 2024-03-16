#pragma once
#include <mutex>
#include <string>
#include <unordered_map>

#include "DataManagerBase.h"

namespace MurphEngine
{
    class TextData;

class TextManager final :
    public DataManagerBase
{

public:
    TextManager(ResourceManager* pResourceManager);
    virtual ~TextManager() override;
    virtual ResourceMetaData* AddFileToMap(std::pair<std::string, ResourceMetaData*> dataPair) override;
    virtual std::string* GetText(const std::string& filepath) override;
    virtual ResourceMetaData* GetMetaData(const std::string& filepath) override;
    virtual void RemoveFileFromMap(const std::string& filepath) override;
    virtual void RemoveReference(const std::string& filepath) override;

private:
};

}
