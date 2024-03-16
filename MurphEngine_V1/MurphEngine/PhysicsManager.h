#pragma once

#include <unordered_map>

#include "Box2DContactListener.h"

class b2World;

namespace MurphEngine
{
    class IActor;
    class ActorManager;

    class PhysicsManager
{
    ActorManager* m_actorManager;
    std::unordered_map<b2Fixture* , IActor*> m_ActorFixtureAssociationMap;
    float m_xGravity;
    float m_yGravity;
    b2World* m_pWorld;
    Box2DContactListener* m_contactListener;

public:
    PhysicsManager(ActorManager* pManager,float xGravity, float yGravity);
    ~PhysicsManager();
    void Initialize();
    void Update([[maybe_unused]] double deltaTime) const;
    b2World* GetWorld() const { return m_pWorld; }

    void AssignFixtureToActor(b2Fixture* pFixture, IActor* pOwnerActor);
    void RemoveFixtureActorAssociationFromMap(b2Fixture* pFixture);
private:

    void ClearActorFixtureMap() { m_ActorFixtureAssociationMap.clear(); }
};

}
