#include "pch.h"
#include "IActor.h"


#include "SpriteComponent.h"
#include "ResourceManager.h"
#include "Bleach_New/BleachNew.h"

/**
 * \brief Spawn Actor at given location.
 * \param system system actor belongs in
 * \param x X start location
 * \param y Y start location
 */
MurphEngine::IActor::IActor(ISystem* system, ActorManager* manager, float x, float y)
    : m_pSystem(system)
    , m_pManager(manager)
    , m_actorLocation{ x, y }
    , m_actorSize(0, 0)
    , m_pSprite(BLEACH_NEW(SpriteComponent(this, m_actorLocation.m_x, m_actorLocation.m_y, m_actorSize.m_x, m_actorSize.m_y)))
{
}

MurphEngine::IActor::IActor(ISystem* system, ActorManager* manager, float x, float y, float width, float height)
    : m_pSystem(system)
    , m_pManager(manager)
    , m_actorLocation{ x, y }
    , m_actorSize(width, height)
    , m_pSprite(nullptr)
{
    m_pSprite = BLEACH_NEW(SpriteComponent(this, m_actorLocation.m_x, m_actorLocation.m_y, m_actorSize.m_x, m_actorSize.m_y));
}

MurphEngine::IActor::IActor(ISystem* system, ActorManager* manager, float x, float y, const char* spriteImage)
    : m_pSystem(system)
    , m_pManager(manager)
    , m_actorLocation{ x, y }
    , m_actorSize(0, 0)
    , m_pSprite(nullptr)
{
    m_pSprite = BLEACH_NEW(SpriteComponent(this, m_actorLocation.m_x, m_actorLocation.m_y, m_actorSize.m_x, m_actorSize.m_y, spriteImage));
}

/**
 * \brief Create actor without pre-determined X and Y. default X:10, Y:10
 * \param system system actor belongs in
 */
MurphEngine::IActor::IActor(ISystem* system, ActorManager* manager)
    : m_pSystem(system)
    , m_pManager(manager)
    , m_actorLocation{ 10, 10 }
    , m_actorSize(0, 0)
    , m_pSprite(BLEACH_NEW(SpriteComponent(this, m_actorLocation.m_x, m_actorLocation.m_y, m_actorSize.m_x, m_actorSize.m_y)))
{
}

MurphEngine::IActor::~IActor()
{
    for (auto& componentMap : m_componentStringMap)
    {
        BLEACH_DELETE(componentMap.second);
    }
    BLEACH_DELETE(m_pSprite);
    m_pSprite = nullptr;

    m_componentStringMap.clear();
}

void MurphEngine::IActor::RemoveComponent(const std::string& id)
{
    m_componentStringMap.erase(id);
}

MurphEngine::IComponent* MurphEngine::IActor::AddComponent(IComponent* pComponent)
{
    //will try to emplace, if already exists, then don't add.
    auto local = m_componentStringMap.try_emplace(pComponent->GetStringID(), pComponent);
    if (local.second)
    {
        return local.first->second;
    }

    return nullptr;
}

MurphEngine::IComponent* MurphEngine::IActor::GetComponent(const std::string& id) const
{
    if (m_componentStringMap.empty())
    {
        return nullptr;
    }
    for (auto& componentMap : m_componentStringMap)
    {
        if (componentMap.first == id)
        {
            return componentMap.second;
        }
    }

    //This will return null if the specified component is not found.
    return nullptr;
}

/**
 * \brief Set Actor Location.
 * \param x new X Location
 * \param y new Y Location
 */ 
void MurphEngine::IActor::SetLocation(float x, float y)
{
    m_actorLocation.m_x = x;
    m_actorLocation.m_y = y;
}

/**
 * \brief Update player location based on increase/decrease of X and Y
 * \param x current location X + value
 * \param y current location Y + value
 */
void MurphEngine::IActor::UpdateLocation(float x, float y)
{
    m_actorLocation.m_x += x;
    m_actorLocation.m_y += y;
}

void MurphEngine::IActor::HandleEvent(Message event) const
{
    for (const auto& component : m_componentStringMap)
    {
        component.second->HandleEvent(event);
    }
}

void MurphEngine::IActor::HandleCollisionEvent(Message collisionEvent, IActor* pActor, IActor* pOther) const
{
    for (const auto& component : m_componentStringMap)
    {
        component.second->HandleCollisionEvent(collisionEvent, pActor, pOther);
    }
}

void MurphEngine::IActor::SetSize(float width, float height)
{
    m_actorSize.m_x = width;
    m_actorSize.m_y = height;
}

/**
 * \brief Update Actor and components.
 */
void MurphEngine::IActor::Update([[maybe_unused]] double deltaTime) const
{
    for (const auto& componentMap : m_componentStringMap)
    {
        componentMap.second->Update(deltaTime);
    }
    m_pSprite->Update(deltaTime);
}

/**
 * \brief Render Actor and components.
 */
void MurphEngine::IActor::Render() const
{
    m_pSprite->Render();
}

