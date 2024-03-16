#include "EnemyMove.h"

#include "../MurphEngine/ActorManager.h"
#include "../MurphEngine/DynamicCollider.h"


EnemyMove::EnemyMove(MurphEngine::IActor* ownerActor, float patrolWidth, float dropHeight)
    : MovementComponent(ownerActor)
    , m_limitFromStart(patrolWidth)
    , m_startXPosition(ownerActor->GetX())
    , m_startYPosition(ownerActor->GetY())
    , m_VerticalDropDistance(dropHeight)
    , m_xVelocityStorage(-1.0)
    , m_isMovingHorizontally(true)
{
    SetNewMovementSpeed(.5);
    m_id = "EnemyMove";
}

void EnemyMove::Update([[maybe_unused]]double deltaTime)
{
    auto collider = static_cast<MurphEngine::DynamicCollider*>(m_pOwnerActor->GetComponent("EnemyShipCollider"));

    if (m_isMovingHorizontally && collider->GetVelocityX() == 0.0)
    {
        collider->SetVelocityX(-1.0 * m_movementSpeed);
    }

    const float lowerLimit = m_startXPosition - m_limitFromStart;
    const float upperLimit = m_startXPosition + m_limitFromStart;
    const float verticalLimit = m_startYPosition + m_VerticalDropDistance;

    const bool isAtLowerLimit = m_pOwnerActor->GetX() < lowerLimit;
    const bool isAtUpperLimit = m_pOwnerActor->GetX() > upperLimit;


    // if we hit our limits for X Movement
    if (isAtLowerLimit || isAtUpperLimit)
    {
        if (m_isMovingHorizontally)
        {
            if ((isAtLowerLimit && collider->GetVelocityX() < 0.0) || (isAtUpperLimit && collider->GetVelocityX() > 0.0))
            {
                m_xVelocityStorage = -collider->GetVelocityX();
                collider->SetVelocityX(0.0);
                collider->SetVelocityY(1.0 * m_movementSpeed);
                m_isMovingHorizontally = false;
            }
            if (isAtUpperLimit && collider->GetVelocityX() > 0.0)
            {
                m_xVelocityStorage = -collider->GetVelocityX();
                collider->SetVelocityX(0.0);
                collider->SetVelocityY(1.0 * m_movementSpeed);
                m_isMovingHorizontally = false;
            }
        }

    }

    if (m_pOwnerActor->GetY() >= verticalLimit)
    {
        if (m_pOwnerActor->GetY() >= 900.0f)
        {
            collider->SetVelocityX(0.0);
            collider->SetVelocityY(0.0);
            return;
        }

        if (!m_isMovingHorizontally)
        {
            collider->SetVelocityX(m_xVelocityStorage);
            collider->SetVelocityY(0);
            m_isMovingHorizontally = true;
        }
        m_startYPosition = m_pOwnerActor->GetY() + m_VerticalDropDistance;
    }

    if (m_pOwnerActor->GetY() >= static_cast<float>(m_pOwnerActor->GetSystem()->GetWindowHeight()))
    {
        m_pOwnerActor->GetManager()->QueueRemovePlayer();
    }
}
