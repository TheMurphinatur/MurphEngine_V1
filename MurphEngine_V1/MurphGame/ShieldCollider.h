#pragma once
#include "../MurphEngine/StaticCollider.h"

class ShieldCollider final :
    public MurphEngine::StaticCollider
{
public:
    ShieldCollider(MurphEngine::IActor* pOwner);
    virtual void HandleCollisionEvent(MurphEngine::Message collisionEvent, MurphEngine::IActor* pActor,
        MurphEngine::IActor* OtherActor) override;
};

