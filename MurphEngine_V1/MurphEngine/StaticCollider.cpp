#include "pch.h"
#include "StaticCollider.h"

#include <box2d/b2_body.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_world.h>

#include "ActorManager.h"
#include "DynamicCollider.h"

#define COLLIDER_OVERLAY 0


MurphEngine::StaticCollider::StaticCollider(IActor* pOwner)
    : MovementComponent(pOwner)
    , m_pParentWorld(nullptr)
    , m_pBody(nullptr)
    , m_pFixture(nullptr)
{
    m_pOwnerActor = pOwner;
}

MurphEngine::StaticCollider::~StaticCollider()
{
    m_pOwnerActor->GetManager()->GetPhysicsManager()->RemoveFixtureActorAssociationFromMap(m_pFixture);

    if (m_pBody != nullptr)
    {
        if (m_pFixture != nullptr)
        {
            m_pBody->DestroyFixture(m_pFixture);
        }

        m_pParentWorld->DestroyBody(m_pBody);
    }
}

void MurphEngine::StaticCollider::Initialize()
{
    m_pParentWorld = m_pOwnerActor->GetManager()->GetPhysicsManager()->GetWorld();
    m_colliderWidth = m_pOwnerActor->GetWidth();
    m_colliderHeight = m_pOwnerActor->GetHeight();

    float colliderHalfWidth = m_colliderWidth / 2.0f;
    float colliderHalfHeight = m_colliderHeight / 2.0f;

    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(m_pOwnerActor->GetX() + colliderHalfWidth, m_pOwnerActor->GetY() + colliderHalfHeight);

    m_pBody = m_pParentWorld->CreateBody(&bodyDef);

    b2PolygonShape shape;
    shape.SetAsBox(colliderHalfWidth, colliderHalfHeight);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;

    m_pFixture = m_pBody->CreateFixture(&fixtureDef);

    m_pOwnerActor->GetManager()->GetPhysicsManager()->AssignFixtureToActor(m_pFixture, m_pOwnerActor);
}



void MurphEngine::StaticCollider::Render()
{
#if COLLIDER_OVERLAY
    SDL_Rect localRect;
    auto& position = m_pBody->GetTransform();
    auto colliderHalfWidth = m_colliderWidth / 2;
    auto colliderHalfHeight = m_colliderHeight / 2;
    localRect.w = static_cast<int>(m_colliderWidth);
    localRect.h = static_cast<int>(m_colliderHeight);

    localRect.x = static_cast<int>(position.p.x - colliderHalfWidth);
    localRect.y = static_cast<int>(position.p.y - colliderHalfHeight);

    m_pOwnerActor->GetSystem()->GetGraphics()->SetDrawColor(255, 255, 0, 255);
    SDL_RenderDrawRect(m_pOwnerActor->GetSystem()->GetGraphics()->GetRenderer(),  &localRect);
#endif
}


