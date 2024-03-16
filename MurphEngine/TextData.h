#pragma once
#include <mutex>
#include <string>

#include "ResourceMetaData.h"

namespace MurphEngine
{
    
class TextData final :
    public ResourceMetaData
{
    std::string m_textData;
    std::mutex m_textDataMutex;


public:
    virtual ~TextData() override;
    void SetTextData(const std::string text);
    std::string* GetText();
private:
    void ClearTextData();
};

}
