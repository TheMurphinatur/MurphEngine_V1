#include "TextureData.h"

#include <SDL_render.h>

void MurphEngine::TextureData::ClearTexture()
{
    SDL_DestroyTexture(m_pTexture);
    m_pTexture = nullptr;
}
