#include "EnemyFiringComponent.h"

#include "ActorFactory.h"
#include <random>


EnemyFiringComponent::EnemyFiringComponent(MurphEngine::IActor* pOwner, ActorFactory* factory)
    : m_factory(factory)
{
    m_pOwnerActor = pOwner;
    m_id = "EnemyFiringComponent";
}

void EnemyFiringComponent::Update(double deltaTime)
{
    if (m_shotTimer >= m_shotDelay)
    {
        static thread_local std::mt19937 m_generator;
        std::uniform_int_distribution<int> distribution(0, 100);
        int randomValue = distribution(m_generator);
        if (randomValue < m_percentChanceToFire)
        {
            // shoot
            m_factory->CreateEnemyBullet(m_pOwnerActor->GetX() + m_pOwnerActor->GetWidth() / 2, m_pOwnerActor->GetY());
        }
        m_shotTimer = 0;
    }
    m_shotTimer += deltaTime;
}

void EnemyFiringComponent::SetChanceToFire(float percentChance)
{
    m_percentChanceToFire = std::clamp(percentChance, 0.f, 100.f);
}
