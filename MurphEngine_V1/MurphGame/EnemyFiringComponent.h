#pragma once
#include "..\MurphEngine\ProjectileGenerationComponent.h"


class ActorFactory;

class EnemyFiringComponent final :
    public MurphEngine::ProjectileGenerationComponent
{
    double m_shotDelay = 1500.0;
    double m_shotTimer = 0;
    float m_percentChanceToFire = 3;
    ActorFactory* m_factory;
public:
    
    EnemyFiringComponent(MurphEngine::IActor* pOwner, ActorFactory* factory);
    virtual void Update(double deltaTime) override;

    void SetShotDelayMs(double delayMs) { m_shotDelay = delayMs; }
    void SetChanceToFire(float percentChance);
};

