#include "pch.h"
#include "ActorManager.h"

#include <cassert>

#include "SpriteComponent.h"
#include "Bleach_New/BleachNew.h"

/**
 * \brief Create an actor manager for the system.
 * \param system system we are managing actors for
 * \param estimatedMaxActors estimated count of actors in the game. This is mainly for vector size reservation
 */
MurphEngine::ActorManager::ActorManager(ISystem* system, size_t estimatedMaxActors)
    : m_pSystem(system)
    , m_pPhysicsManager(BLEACH_NEW(PhysicsManager(this, 0.0f, 0.0f)))
    , m_pPlayerActor(nullptr)
{
    m_pActors.reserve(estimatedMaxActors);
    m_pPhysicsManager->Initialize();
}

MurphEngine::ActorManager::~ActorManager()
{
    BLEACH_DELETE(m_pPlayerActor);
    for (auto pActor : m_pActors)
    {
        BLEACH_DELETE(pActor.second);
        pActor.second = nullptr;
    }
    m_pActors.clear();

    BLEACH_DELETE(m_pPhysicsManager);
}

/**
 * \brief Creates a new actor if player has not been created already. if already created, will update X and Y
 * \param x player location X
 * \param y player location Y
 * \return player pointer.
 */
MurphEngine::IActor* MurphEngine::ActorManager::AddPlayer(float x, float y, const char* spriteFilePath)
{
    if (m_pPlayerActor == nullptr)
    {
        m_pPlayerActor = BLEACH_NEW(IActor(m_pSystem, this, x, y, spriteFilePath));
        return m_pPlayerActor;
    }
    assert(m_pPlayerActor != nullptr);

    return m_pPlayerActor;// return a pointer to player actor.

}

MurphEngine::IActor* MurphEngine::ActorManager::AddActor(size_t actorNumber, float x, float y)
{
    //add the actor to the end of the vector
    auto newActor = BLEACH_NEW(IActor(m_pSystem, this, x, y));
    newActor->SetNumber(actorNumber);
    m_pActors.emplace_back(actorNumber, newActor);

    // we know the actor is at the back so, we just return a pointer to the actor at the back.
    return m_pActors.back().second;

}

MurphEngine::IActor* MurphEngine::ActorManager::AddActor(size_t actorNumber, float x, float y, float width, float height)
{
    //add the actor to the end of the vector
    auto newActor = BLEACH_NEW(IActor(m_pSystem, this, x, y, width, height));
    newActor->SetNumber(actorNumber);
    m_pActors.emplace_back(actorNumber, newActor);

    // we know the actor is at the back so, we just return a pointer to the actor at the back.
    return m_pActors.back().second;
}

/**
 * \brief Find actor by name. nullptr if not found.
 * \param actorNumber Number assigned on creation
 * \return nullptr if not found
 */
MurphEngine::IActor* MurphEngine::ActorManager::GetActorByNumber(size_t actorNumber)
{
    for (auto actorIter = m_pActors.begin(); actorIter != m_pActors.end(); ++actorIter)
    {
        if (*&actorIter->first == actorNumber)
        {
            return &*actorIter->second;
        }
    }
    //we found nothing.
    return nullptr;
}

/**
 * \brief Remove player from manager. WARNING: Must call AddPlayer() again
 */
void MurphEngine::ActorManager::QueueRemovePlayer()
{
    m_isReadyToDeletePlayer = true;
}

/**
 * \brief Delete actor with actorName.
 * \param actorNumber Actor name assigned on creation to delete
 */
void MurphEngine::ActorManager::QueueRemoveActor(size_t actorNumber)
 {
    bool wasFound = false;
    for (auto actorIter = m_pActors.begin(); actorIter != m_pActors.end(); ++actorIter)
    {
        // if the actor name is the same as the location in the iterator
        if (*&actorIter->first == actorNumber)
        {
            m_pActorsToDelete.emplace_back(actorNumber);
            wasFound = true;
            return;
        }
    }
    if (!wasFound)
    {
        Log::LogToFile("Failed to find and remove Actor using given name.");
    }
}

void MurphEngine::ActorManager::SendMessage(Message content) const
{
    if (m_pPlayerActor != nullptr)
        m_pPlayerActor->HandleEvent(content);

    for (const auto& pActor : m_pActors)
    {
        if (pActor.second != nullptr)
        {
            pActor.second->HandleEvent(content);
        }
    }
}

void MurphEngine::ActorManager::SendCollisionMessage(Message content, IActor* pActor, IActor* pOtherActor) const
{
    if (m_pPlayerActor != nullptr)
    {
        m_pPlayerActor->HandleCollisionEvent(content, pActor, pOtherActor);

        for (const auto& ActorInList : m_pActors)
        {
            if (ActorInList.second != nullptr)
            {
                ActorInList.second->HandleCollisionEvent(content, pActor, pOtherActor);
            }
        }
    }
}

/**
 * \brief Update player, then all other actors.
 * \param deltaTime delta time
 */
void MurphEngine::ActorManager::Update([[maybe_unused]] double deltaTime)
{
    if (m_pPlayerActor != nullptr)
    {
        m_pPlayerActor->Update(deltaTime);

        for (const auto& pActor : m_pActors)
        {
            pActor.second->Update(deltaTime);
        }
        m_pPhysicsManager->Update(deltaTime);
    }

    if (!m_pActorsToDelete.empty())
    {
        if (m_isReadyToDeletePlayer)
        {
            BLEACH_DELETE(m_pPlayerActor);
            m_pPlayerActor = nullptr;
        }

        for (const auto& pActorsToDelete : m_pActorsToDelete)
        {
            for (auto actorIter = m_pActors.begin(); actorIter != m_pActors.end(); ++actorIter)
            {
                // if the actor name is the same as the location in the iterator
                if (*&actorIter->first == pActorsToDelete)
                {
                    BLEACH_DELETE(&*actorIter->second);
                    m_pActors.erase(actorIter);
                    return;
                }
            }
        }
        // now that we went through and deleted each, lets clear the vector for a new set of targets.
        m_pActorsToDelete.clear();
    }

}

/**
 * \brief Update Player Only
 * \param deltaTime delta time
 */
void MurphEngine::ActorManager::UpdatePlayerOnly([[maybe_unused]] double deltaTime) const
{
    if (m_pPlayerActor != nullptr)
        m_pPlayerActor->Update(deltaTime);
}

/**
 * \brief Update All Actors EXCEPT the Player
 * \param deltaTime delta time
 */
void MurphEngine::ActorManager::UpdateActorsExceptPlayer([[maybe_unused]] double deltaTime) const
{
    for (const auto& pActor : m_pActors)
    {
        if (pActor.second != nullptr)
        {
            pActor.second->Update(deltaTime);
        }
    }
}

/**
 * \brief Render Player then rest of the actors 
 */
void MurphEngine::ActorManager::Render() const
{
    m_pSystem->StartDrawing();

    //assert(m_pPlayerActor != nullptr);
    if (m_pPlayerActor != nullptr)
        m_pPlayerActor->Render();

    for (const auto& pActor : m_pActors)
    {
        pActor.second->Render();
    }

    m_pSystem->PresentGraphics();
}

/**
 * \brief Render Player Only
 */
void MurphEngine::ActorManager::RenderPlayerOnly() const
{
    if (m_pPlayerActor != nullptr)
        m_pPlayerActor->Render();
}

/**
 * \brief Render All objects EXCEPT Player
 */
void MurphEngine::ActorManager::RenderActorsExceptPlayer() const
{
    for (const auto& pActor : m_pActors)
    {
        pActor.second->Render();
    }
}
