#include "KillerCollider.h"

#include <box2d/b2_body.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_world.h>

#include "ActorManager.h"
#include "PlayerCollider.h"
#include "ResourceManager.h"

MurphEngine::KillerCollider::KillerCollider(IActor* pOwner)
    : DynamicCollider(pOwner)
{
    m_velocityY = 1;
    m_textReference = "../Logging/EnemyTextTest.txt";
}

void MurphEngine::KillerCollider::Render()
{
    DynamicCollider::Render();
}

void MurphEngine::KillerCollider::Shutdown()
{
    DynamicCollider::Shutdown();
}

void MurphEngine::KillerCollider::HandleCollisionEvent(Message collisionEvent, IActor* pActor, IActor* OtherActor)
{
    if (OtherActor == nullptr)
        return;

    if (collisionEvent.GetID() == std::string("Collision") && pActor == this->m_pOwnerActor)
    {
        if (OtherActor != nullptr && OtherActor->GetComponent("PlayerCollider") != nullptr)
        {
            OtherActor->GetManager()->QueueRemoveActor(OtherActor->GetNumber());
            OtherActor->GetManager()->QueueRemovePlayer();
        }
    }
}


