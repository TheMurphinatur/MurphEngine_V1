#include "pch.h"
#include "SpriteComponent.h"

#include <SDL_image.h>

#include "ResourceManager.h"


MurphEngine::SpriteComponent::SpriteComponent(IActor* ownerActor, float x, float y, float w, float h, uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
    : m_spriteTransform{ static_cast<int>(x), static_cast<int>(y), static_cast<int>(w), static_cast<int>(h) }
    , m_color(red, green, blue, alpha)
    , m_pTexture(nullptr)
{
    m_id = "SpriteComponent";
    m_pOwnerActor = ownerActor;
}

MurphEngine::SpriteComponent::SpriteComponent(IActor* ownerActor, float x, float y, float w, float h, const char* imageLocation)
    : m_spriteTransform(SDL_Rect{ static_cast<int>(x),static_cast<int>(y),static_cast<int>(w),static_cast<int>(h) })
    , m_color(0,0,0,0)
    , m_pTexture(nullptr)
{
    m_pOwnerActor = ownerActor;
    GetTexture(imageLocation);
}

void MurphEngine::SpriteComponent::Update([[maybe_unused]] double deltaTime)
{
    // UpdateThreadedFunction sprite location to match Owner location.
    m_spriteTransform.x = static_cast<int>(m_pOwnerActor->GetX());
    m_spriteTransform.y = static_cast<int>(m_pOwnerActor->GetY());
    m_spriteTransform.w = static_cast<int>(m_pOwnerActor->GetWidth());
    m_spriteTransform.h = static_cast<int>(m_pOwnerActor->GetHeight());
    //handle any sprite visual updates if necessary

}

void MurphEngine::SpriteComponent::Render()
{
    if (m_pTexture != nullptr)
    {
        //todo: split this into 4 local variables before assignment.
        SDL_Rect localRect = { static_cast<int>(m_pOwnerActor->GetX()), static_cast<int>(m_pOwnerActor->GetY()), static_cast<int>(m_pOwnerActor->GetWidth()), static_cast<int>(m_pOwnerActor->GetHeight()) };
        SDL_RenderCopy(m_pOwnerActor->GetSystem()->GetGraphics()->GetRenderer(), m_pTexture, nullptr, &localRect);
    }
    else
    {
        m_pOwnerActor->GetSystem()->GetGraphics()->SetDrawColor(m_color.red, m_color.green, m_color.blue, m_color.alpha);
        SDL_RenderFillRect(m_pOwnerActor->GetSystem()->GetGraphics()->GetRenderer(), &m_spriteTransform);
    }
    //Render the component
}


void MurphEngine::SpriteComponent::GetTexture(const char* filename)
{
    m_pTexture = m_pOwnerActor->GetSystem()->GetResourceManager()->GetImage(filename);
}

void MurphEngine::SpriteComponent::SetSpriteColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
{
    m_color.red = red;
    m_color.green = green;
    m_color.blue = blue;
    m_color.alpha = alpha;
}