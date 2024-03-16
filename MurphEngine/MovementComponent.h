#pragma once
#include "IComponent.h"

namespace MurphEngine
{
    class MovementComponent :
        public IComponent
    {
    protected:
        double m_movementSpeed;
        float m_colliderWidth = 0;
        float m_colliderHeight = 0;
    public:
        enum entityCategory //TODO: this is for collision filtering in Box2D. need to look into this, make masks, etc.
        {
            kShield = 0x0001,
            kPlayerShip = 0x0002,
            kPlayerbullet = 0x0004,
            kEnemyShip = 0x0008,
            kEnemyBullet = 0x0010,
        };
        virtual void Initialize() override;
        virtual void Update([[maybe_unused]] double deltaTime) override;
        virtual void Render() override;
        virtual void Shutdown() override;
        MovementComponent(IActor* ownerActor);

        void UpdateX(float newX) const { m_pOwnerActor->SetX(newX); }
        void UpdateY(float newY) const { m_pOwnerActor->SetY(newY); }


        //Movement speed functions
        // Set new Movement speed
        void SetNewMovementSpeed(double newSpeed) { m_movementSpeed = newSpeed; }
        // Get Current Movement Speed (double)
        [[nodiscard]] double GetMovementSpeed() const { return m_movementSpeed; }
    };
}



