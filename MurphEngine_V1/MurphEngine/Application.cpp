#include "pch.h"

#include <iostream>


#include "Application.h"

#include <cassert>
#include <sstream>


#include "ResourceManager.h"
#include "WindowsSystem.h"
#include "Bleach_New/BleachNew.h"

#define FPS_LOGGING 1
#define LOGGING_VERBOSITY_FULL 0

MurphEngine::Application::Application()
    : m_pSystem(BLEACH_NEW(WindowsSystem()))
    , m_deltaTime(0)
    , m_pActorManager(nullptr)
{
}

MurphEngine::Application::~Application()
{
   BLEACH_DELETE(m_pSystem);
}


void MurphEngine::Application::ApplicationInitialize()
{
    Log::InitializeLog(); // Initialize our logging capability when we init the engine.

#if  LOGGING_VERBOSITY_FULL
    Log::LogToFile("Engine Init");
#endif


    m_pSystem->CreateSystemWindow("Space Invaders Murph Edition.", 50, 50, 800, 800);
    m_pSystem->Initialize();
    assert(m_pSystem != nullptr);
    m_pActorManager = BLEACH_NEW(ActorManager(m_pSystem, 10));

}

bool MurphEngine::Application::Update(double deltaTime)
{
#if LOGGING_VERBOSITY_FULL
    Log::LogToFile("Engine UpdateThreadedFunction");
#endif

    m_pSystem->GetResourceManager()->UpdateMainFunction();
    m_pActorManager->Update(deltaTime);
    return m_pSystem->ProcessEvents(deltaTime);
}

void MurphEngine::Application::Render()
{
    m_pSystem->GetGraphics()->SetDrawColor(50, 50, 50, 255);
    m_pActorManager->Render();
#if LOGGING_VERBOSITY_FULL
    Log::LogToFile("Engine Render");
#endif
}

void MurphEngine::Application::ApplicationShutdown()
{
    Log::LogToFile("Engine Shutdown");
    BLEACH_DELETE(m_pActorManager);
    m_pSystem->SystemShutDown();
}



void MurphEngine::Application::Main()
{

    ApplicationInitialize();
    static int frameCount = 0;
    static double frameTime = 0;
    do
    {
        ++frameCount;
        m_frameTimer.StartTimer();

        bool canContinue = Update(m_deltaTime);

        m_pActorManager->Update(m_deltaTime);
        Render();
        m_isPlaying = canContinue;


        m_deltaTime = m_frameTimer.GetDeltaFromStart();

#if FPS_LOGGING
        frameTime += m_deltaTime;
        if (frameTime >= 1000)
        {
            std::stringstream ss;

            ss << "FPS: " << frameCount;
            MurphEngine::Log::LogToConsole(ss.str().c_str());
            frameCount = 0;
            frameTime -= 1000;
        }
#endif
    }
    while (m_isPlaying);

    ApplicationShutdown();
}
