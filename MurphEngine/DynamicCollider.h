#pragma once
#include "MovementComponent.h"

class b2Fixture;
class b2Body;
class b2World;

namespace MurphEngine
{
    
class DynamicCollider :
    public MovementComponent
{
protected:
    b2World* m_pParentWorld;
    b2Body* m_pBody;
    b2Fixture* m_pFixture;
    double m_velocityX = 0;
    double m_velocityY = 0;

public:
    DynamicCollider(IActor* pOwner);
    virtual ~DynamicCollider() override;

    virtual void Initialize() override;
    virtual void Update([[maybe_unused]] double deltaTime) override;
    virtual void Render() override;

    b2Fixture* GetFixture() const { return m_pFixture; }


    double GetVelocityX() const { return m_velocityX; }
    double GetVelocityY() const { return m_velocityY; }
    void SetVelocityY(double velocityY) { m_velocityY = velocityY; }
    void SetVelocityX(double velocityX) { m_velocityX = velocityX; }

};

}
