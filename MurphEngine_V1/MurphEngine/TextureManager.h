#pragma once
#include <mutex>
#include <SDL_render.h>

#include <unordered_map>


namespace MurphEngine
{
    class ResourceMetaData;
    class ResourceManager;
    class TextureData;


    class TextureManager
    {
        ResourceManager* m_pResourceManager;
        std::unordered_map<const char*, TextureData*> m_loadedTexturesWithMetaData;

    public: 
        TextureManager(ResourceManager* pManager);
        ~TextureManager();
        SDL_Texture* GetOrLoadImage(const char* filepath);

    private:
        bool IsFileLoaded(const char* filepath);
        SDL_Texture* AddFileToMap(const char* filepath);

    };

}
