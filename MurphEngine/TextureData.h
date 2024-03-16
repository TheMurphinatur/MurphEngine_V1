#pragma once
#include <atomic>

#include "ResourceMetaData.h"

struct SDL_Texture;


namespace MurphEngine
{
    
class TextureData final :
    public ResourceMetaData
{
    SDL_Texture* m_pTexture = nullptr;
public:
    SDL_Texture* GetTexture() { return m_pTexture; }
    void SetTexture(SDL_Texture* texture) { m_pTexture = texture; }
    void ClearTexture();
};

}
