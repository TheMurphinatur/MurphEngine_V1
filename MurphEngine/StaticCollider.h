#pragma once
#include "MovementComponent.h"

class b2Body;
class b2World;
class b2Fixture;

namespace MurphEngine
{
    
class StaticCollider :
    public MovementComponent
{
    b2World* m_pParentWorld;
    b2Body* m_pBody;
    b2Fixture* m_pFixture;


public:
    StaticCollider(IActor* pOwner);
    virtual ~StaticCollider() override;

    virtual void Initialize() override;
    virtual void Render() override;
    b2Fixture* GetFixture() const { return m_pFixture; }
};

}
