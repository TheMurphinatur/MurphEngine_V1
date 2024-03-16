#include "DynamicCollider.h"

#include "pch.h"
#include <box2d/b2_world.h>
#include <box2d/b2_body.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_fixture.h>

#include "ActorManager.h"
#include "InputComponent.h"


#define COLLIDER_OVERLAY 0


MurphEngine::DynamicCollider::DynamicCollider(IActor* pOwner)
    : MovementComponent(pOwner)
    , m_pParentWorld(nullptr)
    , m_pBody(nullptr)
    , m_pFixture(nullptr)
{
    m_pOwnerActor = pOwner;
}

MurphEngine::DynamicCollider::~DynamicCollider()
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

void MurphEngine::DynamicCollider::Initialize()
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

    m_pFixture = m_pBody->CreateFixture(&fixtureDef);

    m_pOwnerActor->GetManager()->GetPhysicsManager()->AssignFixtureToActor(m_pFixture, m_pOwnerActor);
}


void MurphEngine::DynamicCollider::Update([[maybe_unused]] double deltaTime)
{
    m_pBody->SetLinearVelocity({ static_cast<float>(m_velocityX * m_movementSpeed), static_cast<float>(m_velocityY * m_movementSpeed) });
    //m_pBody->SetLinearVelocity({ static_cast<float>(m_velocityX), static_cast<float>(m_velocityY) });
    float colliderHalfWidth = m_colliderWidth / 2.0f;
    float colliderHalfHeight = m_colliderHeight / 2.0f;
    auto& position = m_pBody->GetTransform();

    m_pOwnerActor->SetX(position.p.x - colliderHalfWidth);
    m_pOwnerActor->SetY(position.p.y - colliderHalfHeight);

}

void MurphEngine::DynamicCollider::Render()
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

    m_pOwnerActor->GetSystem()->GetGraphics()->SetDrawColor(255, 0, 0, 255);
    SDL_RenderDrawRect(m_pOwnerActor->GetSystem()->GetGraphics()->GetRenderer(), &localRect);
#endif
}




