#pragma once

#include <unordered_map>

#include "Message.h"
#include "Vector2.h"
#include "string"

namespace MurphEngine
{
    class ActorManager;
    class SpriteComponent;
    class ISystem;
    class IComponent;

    class IActor
    {
        ISystem* m_pSystem;
        ActorManager* m_pManager;
        Vector2<float> m_actorLocation;
        size_t m_actorNumber = 0;

        // X = width Y = height
        Vector2<float> m_actorSize;
        SpriteComponent* m_pSprite; //TODO: move into component map

    private:
        std::unordered_map<std::string, IComponent*> m_componentStringMap;
        void SetSystem(ISystem* system) { m_pSystem = system; }
        void SetHeight(float height) { m_actorSize.m_y = height; }
        void SetWidth(float width) { m_actorSize.m_x = width; }

    public:
        IActor() = delete;
        IActor(ISystem* system, ActorManager* manager, float x, float y);
        IActor(ISystem* system, ActorManager* manager, float x, float y, float width, float height);
        IActor(ISystem* system, ActorManager* manager, float x, float y, const char* spriteImage);
        IActor(ISystem* system, ActorManager* manager);
        ~IActor();

        // Component Functions
        void RemoveComponent(const std::string& id);

        IComponent* AddComponent(IComponent* pComponent);
        IComponent* GetComponent(const std::string& id) const;

        [[nodiscard]] ISystem* GetSystem() const { return m_pSystem; }
        [[nodiscard]] SpriteComponent* GetSpriteComponent() const { return m_pSprite; }
        [[nodiscard]] ActorManager* GetManager() const { return m_pManager; }

        // Location based Functions.
        void SetLocation(float x, float y);
        void UpdateLocation(float x, float y);
        void SetX(float value) { m_actorLocation.m_x = value; }
        void SetY(float value) { m_actorLocation.m_y = value; }
        float GetX() const { return m_actorLocation.m_x; }
        float GetY() const { return m_actorLocation.m_y; }
        std::size_t GetNumber() const { return m_actorNumber; }

        // Size Getters and setter
        float GetWidth() const { return m_actorSize.GetX(); }
        float GetHeight() const { return m_actorSize.GetY(); }
        void SetSize(float width, float height);
        void SetNumber(size_t assignedNumber) { m_actorNumber = assignedNumber; }

        // Event
        void HandleEvent(Message event) const;
        void HandleCollisionEvent(Message collisionEvent, IActor* pActor, IActor* pOther) const;

        // Other Functions.
        void Update(double deltaTime) const;
        void Render() const;
    };

}
