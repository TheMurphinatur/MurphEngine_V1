#include "FiringComponent.h"
#include "ActorFactory.h"


FiringComponent::FiringComponent(MurphEngine::IActor* pOwner, ActorFactory* factory)
    : m_factory(factory)
{
    m_pOwnerActor = pOwner;
    m_id = "FiringComponent";
}

void FiringComponent::Update(double deltaTime)
{
    if (m_shotTimer >= m_shotDelay)
    {
        if (m_pOwnerActor->GetSystem()->GetKeyboard()->IsKeyPressed(MurphEngine::MurphKeyboard::MurphKeys::MurphKey_space))
        {
            // shoot
            m_factory->CreateBullet(m_pOwnerActor->GetX() + m_pOwnerActor->GetWidth() / 2, m_pOwnerActor->GetY() - 15);
            // reset shot timer
            m_shotTimer = 0;
        }
    }
    m_shotTimer += deltaTime;
}

