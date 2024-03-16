#include "ShieldCollider.h"
#include "../MurphEngine/ActorManager.h"

ShieldCollider::ShieldCollider(MurphEngine::IActor* pOwner)
    : StaticCollider(pOwner)
{
    m_id = "ShieldCollider";
}

void ShieldCollider::HandleCollisionEvent(MurphEngine::Message collisionEvent, MurphEngine::IActor* pActor,
    MurphEngine::IActor* OtherActor)
{
    if (OtherActor == nullptr)
        return;

    if (collisionEvent.GetID() == std::string("Collision") && pActor == this->m_pOwnerActor)
    {
        m_pOwnerActor->GetManager()->QueueRemoveActor(m_pOwnerActor->GetNumber());
    }
}
