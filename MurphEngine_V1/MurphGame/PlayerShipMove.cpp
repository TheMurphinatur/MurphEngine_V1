#include "PlayerShipMove.h"
#include "../MurphEngine/DynamicCollider.h"

PlayerShipMove::PlayerShipMove(MurphEngine::IActor* pOwner)
    : InputComponent(pOwner)
{
    m_id = "PlayerShipMove";
}


void PlayerShipMove::Update([[maybe_unused]] double deltaTime)
{
    // Make sure we stop movement before we re-evaluate which keys are pressed.
    static_cast<MurphEngine::DynamicCollider*>(m_pOwnerActor->GetComponent("PlayerShipCollider"))->SetVelocityX(0);

    if (m_pOwnerActor->GetSystem()->GetKeyboard()->IsKeyPressed(MurphEngine::MurphKeyboard::MurphKeys::MurphKey_a))
    {
        // left side of screen check
        if (m_pOwnerActor->GetX() > 0)
        {
            static_cast<MurphEngine::DynamicCollider*>(m_pOwnerActor->GetComponent("PlayerShipCollider"))->SetVelocityX(-1 * m_movementSpeed);
        }
    }
    else if (m_pOwnerActor->GetSystem()->GetKeyboard()->IsKeyPressed(MurphEngine::MurphKeyboard::MurphKeys::MurphKey_d))
    {
        // right side of screen check
        if (m_pOwnerActor->GetX() < 800 - m_pOwnerActor->GetWidth())
        {
            static_cast<MurphEngine::DynamicCollider*>(m_pOwnerActor->GetComponent("PlayerShipCollider"))->SetVelocityX(1 * m_movementSpeed);
        }
    }

}
