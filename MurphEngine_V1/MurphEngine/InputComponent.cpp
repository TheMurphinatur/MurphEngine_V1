#include "pch.h"
#include "InputComponent.h"

#include "DynamicCollider.h"

MurphEngine::InputComponent::InputComponent(IActor* pOwner)
    : MovementComponent(pOwner)
{
    SetNewMovementSpeed(1.5);
    m_id = "InputComponent";
}

void MurphEngine::InputComponent::Initialize()
{
}

void MurphEngine::InputComponent::Update([[maybe_unused]] double deltaTime)
{
    static_cast<DynamicCollider*>(m_pOwnerActor->GetComponent("PlayerCollider"))->SetVelocityY(0);

    //Check for Y Direction.
    if (m_pOwnerActor->GetSystem()->GetKeyboard()->IsKeyPressed(MurphKeyboard::MurphKeys::MurphKey_w))
    {      // left side of screen check
        if (m_pOwnerActor->GetY() > 50) // fix this value
        {
            static_cast<DynamicCollider*>(m_pOwnerActor->GetComponent("PlayerCollider"))->SetVelocityY(-1 * m_movementSpeed);
        }
    }
    else if (m_pOwnerActor->GetSystem()->GetKeyboard()->IsKeyPressed(MurphKeyboard::MurphKeys::MurphKey_s))
    {
        if (m_pOwnerActor->GetY() < 900) //fix this value
        {
            static_cast<DynamicCollider*>(m_pOwnerActor->GetComponent("PlayerCollider"))->SetVelocityY(1 * m_movementSpeed);
        }
    }
    // Check for X Direction
    static_cast<DynamicCollider*>(m_pOwnerActor->GetComponent("PlayerCollider"))->SetVelocityX(0);

   if (m_pOwnerActor->GetSystem()->GetKeyboard()->IsKeyPressed(MurphKeyboard::MurphKeys::MurphKey_a))
   {
       // left side of screen check
       if (m_pOwnerActor->GetX() > 0)
       {
           static_cast<DynamicCollider*>(m_pOwnerActor->GetComponent("PlayerCollider"))->SetVelocityX(-1 * m_movementSpeed);
       }
   }
   else if (m_pOwnerActor->GetSystem()->GetKeyboard()->IsKeyPressed(MurphKeyboard::MurphKeys::MurphKey_d))
   {
       // right side of screen check
       if (m_pOwnerActor->GetX() < 1000 - m_pOwnerActor->GetWidth())
       {
           static_cast<DynamicCollider*>(m_pOwnerActor->GetComponent("PlayerCollider"))->SetVelocityX(1 * m_movementSpeed);
       }
   }
}





