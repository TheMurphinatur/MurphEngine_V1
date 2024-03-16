#include "DataManagerBase.h"

#include "Logging.h"
#include "Bleach_New/BleachNew.h"

MurphEngine::DataManagerBase::DataManagerBase(ResourceManager* pResourceManager)
    : m_pResourceManager(pResourceManager)
{
}

bool MurphEngine::DataManagerBase::IsFileLoaded(std::string filepath)
{
    if (const auto search = m_loadedData.find(filepath); search != m_loadedData.end())
        return true;
    else
        return false;
}

