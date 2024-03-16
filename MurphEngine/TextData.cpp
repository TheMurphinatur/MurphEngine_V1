#include "TextData.h"

MurphEngine::TextData::~TextData()
{
    ClearTextData();
}

void MurphEngine::TextData::SetTextData(const std::string text)
{
    //std::lock_guard textLock(m_textDataMutex);
    m_textData = text;
}

std::string* MurphEngine::TextData::GetText()
{
    //std::lock_guard textLock(m_textDataMutex);
    return &m_textData;
}

void MurphEngine::TextData::ClearTextData()
{
    m_textData.erase();
    m_status = kFlushed;
    DecrementRefCount();
}

