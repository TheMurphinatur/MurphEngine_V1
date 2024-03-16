#include "PlayerShipCollider.h"
#include "../MurphEngine/ActorManager.h"
#include "../MurphEngine/Source/Middleware/box2d/b2_body.h"

PlayerShipCollider::PlayerShipCollider(MurphEngine::IActor* pOwner)
    : PlayerCollider(pOwner)
{
    m_id = "PlayerShipCollider";
}

void PlayerShipCollider::Update(double deltaTime)
{
    PlayerCollider::Update(deltaTime);
}

void PlayerShipCollider::HandleCollisionEvent(MurphEngine::Message collisionEvent, MurphEngine::IActor* pActor,
    MurphEngine::IActor* OtherActor)
{
    if (OtherActor == nullptr)
        return;

    if (collisionEvent.GetID() == std::string("Collision") && pActor == this->m_pOwnerActor)
    {
        MurphEngine::Log::LogToConsole("Player Died From Evil Alien.");
        m_pOwnerActor->GetManager()->QueueRemovePlayer();
    }
}
