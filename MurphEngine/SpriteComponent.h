#pragma once
#include <SDL_render.h>
#include <SDL_rect.h>

#include "IComponent.h"

namespace MurphEngine
{
    class SpriteComponent final :
       public IComponent
    {
        struct ColorValues
        {
            uint8_t red;
            uint8_t green;
            uint8_t blue;
            uint8_t alpha;

            ColorValues(uint8_t redValue, uint8_t greenValue, uint8_t blueValue, uint8_t alphaValue)
            {
                red = redValue;
                blue = blueValue;
                green = greenValue;
                alpha = alphaValue;
            }
        };

        SDL_Rect m_spriteTransform;
        ColorValues m_color;
        SDL_Texture* m_pTexture;
    public:
        //static SDL_Texture* s_pTexture;
        SpriteComponent(IActor* ownerActor, float x, float y, float w, float h, uint8_t red = 125, uint8_t green = 0, uint8_t blue = 125, uint8_t alpha = 255);
        SpriteComponent(IActor* ownerActor, float x, float y, float w, float h, const char* imageLocation);

        virtual void Update([[maybe_unused]] double deltaTime) override;
        virtual void Render() override;


        float GetRectWidth() const { return static_cast<float>(m_spriteTransform.w); }
        float GetRectHeight() const { return static_cast<float>(m_spriteTransform.h); }
        void SetWidth(float w) { m_spriteTransform.w = static_cast<int>(w); }
        void SetHeight(float h) { m_spriteTransform.h = static_cast<int>(h); }

        void SetSpriteColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);

        //SDL_Texture* GetTexture() { return s_pTexture; }
        void GetTexture(const char* filename);
    private:
    };


}

