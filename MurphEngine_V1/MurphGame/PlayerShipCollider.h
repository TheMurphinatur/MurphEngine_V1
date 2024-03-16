#pragma once
#include "..\MurphEngine\PlayerCollider.h"
class PlayerShipCollider final :
    public MurphEngine::PlayerCollider
{

public:
    PlayerShipCollider(MurphEngine::IActor* pOwner);
    //virtual ~PlayerShipCollider() override;
    virtual void Update([[maybe_unused]] double deltaTime) override;
    virtual void HandleCollisionEvent(MurphEngine::Message collisionEvent, MurphEngine::IActor* pActor,
        MurphEngine::IActor* OtherActor) override;
};

