#pragma once

#include "../MurphEngine/MovementComponent.h"

class EnemyMove final :
    public MurphEngine::MovementComponent
{
    float m_limitFromStart;
    float m_startXPosition;
    float m_startYPosition;
    float m_VerticalDropDistance;

    double m_xVelocityStorage;

    bool m_isMovingHorizontally;
public:
    EnemyMove(MurphEngine::IActor* ownerActor, float patrolWidth, float dropHeight);

    virtual void Update(double deltaTime) override;
};

