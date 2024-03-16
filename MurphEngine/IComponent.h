#pragma once


#include "ISystem.h"

#include "IActor.h"
namespace MurphEngine
{

    class IComponent
    {
    protected:
        std::string m_id;
        IActor* m_pOwnerActor = nullptr;

    public:
        IComponent() = default;
        IComponent(IActor* ownerActor);
        virtual ~IComponent() = default;

        std::string& GetStringID() { return m_id; }

        virtual void Initialize() { }
        virtual void Update([[maybe_unused]] double deltaTime) = 0;
        virtual void HandleEvent([[maybe_unused]] Message event) { }
        virtual void HandleCollisionEvent([[maybe_unused]] Message collisionEvent,[[maybe_unused]] IActor* pActor, [[maybe_unused]] IActor* OtherActor) { }
        virtual void Render() { }
        virtual void Shutdown() { }
    };

}

