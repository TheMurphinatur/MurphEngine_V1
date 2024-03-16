#include "pch.h"
#include "MurphKeyboard.h"




#include "Logging.h"



MurphEngine::MurphKeyboard::MurphKeyboard()
{
    Initialize();
}

void MurphEngine::MurphKeyboard::OnSDLKeyboardPress(const SDL_Keycode& key)
{
    //TODO check if in vector already, if not, emplace.

    for (auto& iter : m_keysPressed)
    {
        if (iter.first == static_cast<MurphKeys>(key))
        {
            iter.second = true;
            return;
        }
    }
    m_keysPressed.emplace_back(static_cast<MurphKeys>(key), true);

}

bool MurphEngine::MurphKeyboard::IsKeyPressed(const MurphKeys& key) const
{
    for (const auto& iter : m_keysPressed)
    {
        if (iter.first == static_cast<MurphKeys>(key))
        {
            return iter.second;
        }
    }
    return false;
}

void MurphEngine::MurphKeyboard::OnSDLKeyRelease(const SDL_Keycode& key)
{
    for (auto& iter : m_keysPressed)
    {
        if (iter.first == static_cast<MurphKeys>(key))
        {
            iter.second = false;
            return;
        }
    }
}
