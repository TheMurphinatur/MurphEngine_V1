#include "pch.h"
#include "MovementComponent.h"

MurphEngine::MovementComponent::MovementComponent(IActor* ownerActor)
    : m_movementSpeed(0.1)
{
    m_pOwnerActor = ownerActor;
}

void MurphEngine::MovementComponent::Initialize()
{
}

void MurphEngine::MovementComponent::Update([[maybe_unused]] double deltaTime)
{
    //auto oldLocationX = m_pOwnerActor->GetX();
    //auto oldLocationY = m_pOwnerActor->GetY();


    //if (oldLocationX < 800)
    //{
    //    //TODO update player location Vector2 into a Vector2 float
    //    const float newLocationX = oldLocationX += static_cast<float>(1.0f * GetMovementSpeed());
    //    const float newLocationY = oldLocationY += static_cast<float>(1.0f * GetMovementSpeed());
    //    UpdateX(newLocationX);
    //    UpdateY(newLocationY);
    //}
    //else if (oldLocationX >= 800)
    //{
    //    UpdateX(10);
    //    UpdateY(110);
    //}
}

void MurphEngine::MovementComponent::Render()
{
}

void MurphEngine::MovementComponent::Shutdown()
{
}
