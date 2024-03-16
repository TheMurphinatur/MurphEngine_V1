#pragma once
#include "EventSystem.h"
#include "IActor.h"
#include "Logging.h"
#include "ISystem.h"


namespace MurphEngine
{
    class ActorManager
    {
        ISystem* m_pSystem;
        PhysicsManager* m_pPhysicsManager;

        IActor* m_pPlayerActor;
        std::vector<std::pair<size_t, IActor*>> m_pActors;
        std::vector<size_t> m_pActorsToDelete;

        bool m_isReadyToDeletePlayer = false;

    public:
        ActorManager(ISystem* system, size_t estimatedMaxActors);
        ~ActorManager();

        // Actor Adders
        IActor* AddPlayer(float x, float y, const char* spriteFilePath);
        IActor* AddActor(size_t actorNumber, float x, float y);
        IActor* AddActor(size_t actorNumber, float x, float y, float width, float height);

        // Actor Getters
        IActor* GetPlayer() const { return m_pPlayerActor; }
        IActor* GetActorByNumber(size_t actorNumber);

        // Removal Functions
        void QueueRemovePlayer();
        void QueueRemoveActor(size_t actorNumber);

        //Event TODO: finish Event system?
        void SendMessage(Message content) const;
        void SendCollisionMessage(Message content, IActor* pActor,IActor* pOtherActor) const;

        // UpdateThreadedFunction Options Available:
        void Update([[maybe_unused]] double deltaTime);
        void UpdatePlayerOnly([[maybe_unused]] double deltaTime) const;
        void UpdateActorsExceptPlayer([[maybe_unused]] double deltaTime) const;

        // Render Options Available:
        void Render() const;
        void RenderPlayerOnly() const;
        void RenderActorsExceptPlayer() const;
        [[nodiscard]] PhysicsManager* GetPhysicsManager() const { return m_pPhysicsManager; }


    private:
 
    };


}

