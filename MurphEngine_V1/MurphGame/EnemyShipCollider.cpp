#include "EnemyShipCollider.h"

#include "../MurphEngine/ActorManager.h"
#include "../MurphEngine/Source/Middleware/box2d/b2_body.h"

EnemyShipCollider::EnemyShipCollider(MurphEngine::IActor* pOwner)
    : DynamicCollider(pOwner)
{
    m_id = "EnemyShipCollider";
}

EnemyShipCollider::~EnemyShipCollider()
{
    m_pOwnerActor->GetManager()->GetPhysicsManager()->RemoveFixtureActorAssociationFromMap(m_pFixture);
}

void EnemyShipCollider::Update([[maybe_unused]] double deltaTime)
{
    DynamicCollider::Update(deltaTime);
}

void EnemyShipCollider::HandleCollisionEvent(MurphEngine::Message collisionEvent, MurphEngine::IActor* pActor,
    MurphEngine::IActor* OtherActor)
{
    if (OtherActor == nullptr)
        return;

    if (collisionEvent.GetID() == std::string("Collision") && pActor == this->m_pOwnerActor)
    {
        if (OtherActor->GetComponent("PlayerShipCollider") != nullptr)
        {
            MurphEngine::Log::LogToConsole("Player Died From Evil Alien.");
            m_pOwnerActor->GetManager()->QueueRemoveActor(m_pOwnerActor->GetNumber());
        }
        if (OtherActor->GetComponent("ShieldCollider") != nullptr)
        {
            m_pOwnerActor->GetManager()->QueueRemoveActor(m_pOwnerActor->GetNumber());   
        }
        if (OtherActor->GetComponent("BulletCollider") != nullptr)
        {
            m_pOwnerActor->GetManager()->QueueRemoveActor(m_pOwnerActor->GetNumber());
        }
    }
}


