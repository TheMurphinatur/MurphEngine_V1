#include "EnemyBulletCollider.h"

#include "../MurphEngine/Source/Middleware/box2d/b2_body.h"
#include "../MurphEngine/Source/Middleware/box2d/b2_world.h"
#include "../MurphEngine/Source/Middleware/box2d/b2_polygon_shape.h"
#include "../MurphEngine/Source/Middleware/box2d/b2_fixture.h"

#include "../MurphEngine/ActorManager.h"

EnemyBulletCollider::EnemyBulletCollider(MurphEngine::IActor* pOwner)
    : DynamicCollider(pOwner)
{
    m_id = "EnemyBulletCollider";
}

void EnemyBulletCollider::HandleCollisionEvent(MurphEngine::Message collisionEvent, MurphEngine::IActor* pActor,
                                               MurphEngine::IActor* OtherActor)
{
    if (OtherActor == nullptr)
        return;

    if (collisionEvent.GetID() == std::string("Collision") && pActor == this->m_pOwnerActor)
    {
        if (OtherActor->GetComponent("ShieldCollider") != nullptr)
        {
            m_pOwnerActor->GetManager()->QueueRemoveActor(m_pOwnerActor->GetNumber());
        }
    }
}

void EnemyBulletCollider::Initialize()
{
    m_pParentWorld = m_pOwnerActor->GetManager()->GetPhysicsManager()->GetWorld();
    m_colliderWidth = m_pOwnerActor->GetWidth();
    m_colliderHeight = m_pOwnerActor->GetHeight();

    float colliderHalfWidth = m_colliderWidth / 2.0f;
    float colliderHalfHeight = m_colliderHeight / 2.0f;

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(m_pOwnerActor->GetX() + colliderHalfWidth, m_pOwnerActor->GetY() + colliderHalfHeight);


    m_pBody = m_pParentWorld->CreateBody(&bodyDef);

    b2PolygonShape shape;
    shape.SetAsBox(colliderHalfWidth, colliderHalfHeight);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 1;
    fixtureDef.friction = 1;
    fixtureDef.isSensor = true;

    m_pFixture = m_pBody->CreateFixture(&fixtureDef);

    m_pOwnerActor->GetManager()->GetPhysicsManager()->AssignFixtureToActor(m_pFixture, m_pOwnerActor);


    m_velocityY = 1;
}

void EnemyBulletCollider::Update(double deltaTime)
{
    if (m_pOwnerActor->GetY() > static_cast<float>(m_pOwnerActor->GetSystem()->GetWindowHeight()))
    {
        m_pOwnerActor->GetManager()->QueueRemoveActor(m_pOwnerActor->GetNumber());
        return;
    }

    DynamicCollider::Update(deltaTime);
}
