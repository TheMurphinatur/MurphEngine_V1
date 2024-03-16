#pragma once

#include "../MurphEngine/ProjectileGenerationComponent.h"

class ActorFactory;

class FiringComponent final :
    public MurphEngine::ProjectileGenerationComponent
{
    double m_shotDelay = 500;
    double m_shotTimer = 0;
    ActorFactory* m_factory;
public:
    FiringComponent(MurphEngine::IActor* pOwner, ActorFactory* factory);
    virtual void Update(double deltaTime) override;

    void SetShotDelayMs(double delayMs) { m_shotDelay = delayMs; }
};

