#pragma once

namespace MurphEngine
{
    class ActorManager;
    class IActor;
}

class ActorFactory
{
    MurphEngine::ActorManager* m_pActorManager;
    size_t m_objectCount;
public:
    ActorFactory(MurphEngine::ActorManager* pManager);

    MurphEngine::IActor* CreatePlayer(float x, float y, float w, float h);
    MurphEngine::IActor* CreateEnemyShip(float x, float y, float patrolWidth, float dropHeight, float shipWidth);
    void CreateConcaveShield(float x, float y, float w, float h, size_t elementCount);
    MurphEngine::IActor* CreateSingleShield(float x, float y, float w, float h);
    MurphEngine::IActor* CreateBullet(float x, float y);
    MurphEngine::IActor* CreateEnemyBullet(float x, float y);

    void CreateShipRow(float startY, float startX, float shipSeparation, size_t horizontalCount, float patrolWidth, float dropHeight);

    void CreateSpaceInvadersShield(float x, float y);
};

