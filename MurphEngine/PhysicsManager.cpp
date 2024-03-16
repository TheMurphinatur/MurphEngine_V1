#include "PhysicsManager.h"

#include <box2d/b2_world.h>

#include "ActorManager.h"
#include "Bleach_New/BleachNew.h"


MurphEngine::PhysicsManager::PhysicsManager(ActorManager* pManager, float xGravity, float yGravity)
    : m_actorManager(pManager)
    , m_xGravity(xGravity)
    , m_yGravity(yGravity)
    , m_pWorld(nullptr)
    , m_contactListener(nullptr)
{
}

MurphEngine::PhysicsManager::~PhysicsManager()
{
    BLEACH_DELETE(m_pWorld);
    BLEACH_DELETE(m_contactListener);
    ClearActorFixtureMap();
}

void MurphEngine::PhysicsManager::Initialize()
{
    m_pWorld = BLEACH_NEW(b2World(b2Vec2(m_xGravity, m_yGravity)));
    m_contactListener = BLEACH_NEW(Box2DContactListener());
    m_pWorld->SetContactListener(m_contactListener);
}

void MurphEngine::PhysicsManager::Update([[maybe_unused]] double deltaTime) const
{
    m_pWorld->Step(static_cast<float>(deltaTime), 5, 5);

    const auto& beginOverlapList = m_contactListener->GetBeginContacts();
    for (auto& overlapList : beginOverlapList)
    {
        //auto actorA = m_ActorFixtureAssociationMap.find(overlapList.pFixtureA);
        auto actorA = m_ActorFixtureAssociationMap.find(overlapList.pFixtureA);
        if (actorA == m_ActorFixtureAssociationMap.end())
        {
            return;
        }

        auto actorB = m_ActorFixtureAssociationMap.find(overlapList.pFixtureB);
        if (actorB == m_ActorFixtureAssociationMap.end())
        {
            return;
        }

        m_actorManager->SendCollisionMessage("Collision", actorA->second, actorB->second);
        m_actorManager->SendCollisionMessage("Collision", actorB->second, actorA->second);
    }

    const auto& endOverlapList = m_contactListener->GetEndContacts();
    for (auto& overlapList : endOverlapList)
    {
        auto actorA = m_ActorFixtureAssociationMap.find(overlapList.pFixtureA);
        auto actorB = m_ActorFixtureAssociationMap.find(overlapList.pFixtureB);

    }

    m_contactListener->ClearResults();
}

void MurphEngine::PhysicsManager::AssignFixtureToActor(b2Fixture* pFixture, IActor* pOwnerActor)
{
    m_ActorFixtureAssociationMap.insert(std::make_pair(pFixture, pOwnerActor));
}

void MurphEngine::PhysicsManager::RemoveFixtureActorAssociationFromMap(b2Fixture* pFixture)
{
    m_ActorFixtureAssociationMap.erase(pFixture);
}

