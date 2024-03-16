#pragma once

#include "../MurphEngine/DynamicCollider.h"

class BulletCollider final :
    public MurphEngine::DynamicCollider
{
public:
    BulletCollider(MurphEngine::IActor* pOwner);
    virtual void HandleCollisionEvent(MurphEngine::Message collisionEvent, MurphEngine::IActor* pActor,
        MurphEngine::IActor* OtherActor) override;
    virtual void Initialize() override;
    virtual void Update(double deltaTime) override;
};

