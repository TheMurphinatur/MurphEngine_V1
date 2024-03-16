#pragma once
#include <queue>
#include <SDL_render.h>

#include "TextureManager.h"
#include "TextManager.h"


namespace MurphEngine
{
    class ISystem;
    class ResourceMetaData;

    class ResourceManager
    {
        ISystem* m_pSystem;
        TextureManager m_pTextureManager;
        TextManager m_TextManager;

        std::queue<std::pair<std::string, ResourceMetaData*>> m_loadedQueuePair;
        std::mutex m_loadedPairMutex;

        std::queue<std::pair<std::string, ResourceMetaData*>> m_requestQueuePair;
        std::mutex m_requestPairMutex;

        std::thread m_resourceLoaderThread;
        std::atomic_bool m_ShutDownThreadedFunction = false;

        std::condition_variable m_threadCondition;

    public:
        ResourceManager(ISystem* pSystem);
        ~ResourceManager() = default;
        void Initialize();
        ISystem* GetSystem() const { return m_pSystem; }    
        void ShutDown();
        void UpdateThreadedFunction();
        void UpdateMainFunction();
        
        SDL_Texture* GetImage(const char* filepath);
        std::string* GetText(const std::string& filepath);
        void CacheText(const std::string& filepath);
        bool AddTextReference(const std::string& filepath);
        void RemoveTextReference(const std::string& filepath);
        bool IsTextRefAvailable(const std::string& filepath);


    private:
        void ThreadedTextLoaderFunction();
        void AddToQueueAndNotifyThread(const std::string& filepath);
        void NotifyThread() { m_threadCondition.notify_one(); }

    };

}
