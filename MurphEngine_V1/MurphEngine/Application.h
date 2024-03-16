#pragma once

// Application Header
#include "ActorManager.h"
#include "Logging.h"
#include "ISystem.h"
#include "TimeManager.h"

#pragma once

namespace MurphEngine
{

    class Application
    {
    public:
        ISystem* m_pSystem;
        TimeManager m_frameTimer;
        double m_deltaTime;
    protected:
        ActorManager* m_pActorManager;

    private:
        bool m_isPlaying = true;
       

    protected:
        virtual void ApplicationInitialize();

        virtual bool Update(double deltaTime);
        virtual void Render();
        virtual void ApplicationShutdown();

    public:
        Application();
        virtual ~Application();
        virtual void Main();


    };


}


