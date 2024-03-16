#pragma once

#include "../MurphEngine/DynamicCollider.h"

class EnemyShipCollider final:
    public MurphEngine::DynamicCollider
{

public:
    EnemyShipCollider(MurphEngine::IActor* pOwner);
    virtual ~EnemyShipCollider() override;
    virtual void Update([[maybe_unused]] double deltaTime) override;
    virtual void HandleCollisionEvent(MurphEngine::Message collisionEvent, MurphEngine::IActor* pActor,
        MurphEngine::IActor* OtherActor) override;
};

