#pragma once
#include <vector>
#include <string>

#include "IKeyboard.h"


namespace MurphEngine
{
    class MurphKeyboard :
        public IKeyboard
    {
    public:
        enum MurphKeys
        {
            MurphKey_w = SDLK_w,
            MurphKey_a = SDLK_a,
            MurphKey_s = SDLK_s,
            MurphKey_d = SDLK_d,
            MurphKey_space = SDLK_SPACE,
            MurphKey_esc = SDLK_ESCAPE

        };
    private:
        std::vector<std::pair<MurphKeys, bool>> m_keysPressed;


    public:
        MurphKeyboard();
        void Initialize() { m_keysPressed.reserve(10); }
        void OnSDLKeyboardPress(const SDL_Keycode& key);
        bool IsKeyPressed(const MurphKeys& key) const;

        void OnSDLKeyRelease(const SDL_Keycode& key);
    };

}

