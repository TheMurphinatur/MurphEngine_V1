
#include "GameApplication.h"

#include <cassert>

#include "ActorFactory.h"
//#include "../MurphEngine/IComponent.h"


//#define FPS_LOGGING 1
#define GAME_LOGGING_VERBOSITY_FULL 0


void GameApplication::ApplicationInitialize()
{
    Application::ApplicationInitialize();
    assert(m_pSystem != nullptr);

    MurphEngine::Log::LogToFile("Love2Murph Initialization Begin.");

    static ActorFactory mFactory(m_pActorManager);

    //////////////////////////////////
    // Player
    //////////////////////////////////
    mFactory.CreatePlayer(400, 700, 50, 25);

    //////////////////////////////////
    // ENEMIES
    //////////////////////////////////
    // Ship automatic creation variables. This makes creating multiple rows quickly and easily.
    constexpr float sizeOfHorizontalPatrol = 25;
    constexpr float sizeOfVerticalDrop = 10;
    constexpr float shipSeparation = 32;
    constexpr int horizontalCount = 5;
    float startX = static_cast<float>(m_pSystem->GetWindowWidth()) / 2; // Where is the middle?
    float startY = 75.f; // Where does the top row start?
    constexpr size_t rowCount = 5; // Here, we decide how many rows of enemies we want.

    for (size_t i = 0; i < rowCount; ++i)
    {
        mFactory.CreateShipRow(startY, startX, shipSeparation, horizontalCount, sizeOfHorizontalPatrol, sizeOfVerticalDrop);
        startY += 50.f;
    }

    /////////////////////////////////////////
    //  SHIELDS
    /////////////////////////////////////////
    mFactory.CreateSpaceInvadersShield(125, 600);
    mFactory.CreateSpaceInvadersShield(300, 600);
    mFactory.CreateSpaceInvadersShield(475, 600);
    mFactory.CreateSpaceInvadersShield(650, 600);

#if GAME_LOGGING_VERBOSITY_FULL
    MurphEngine::Log::LogToFile("Love2Murph Object Initialization complete.");
#endif
}

bool GameApplication::Update(double deltaTime)
{
#if GAME_LOGGING_VERBOSITY_FULL
    MurphEngine::Log::LogToFile("Love2Murph UpdateMainLoop");
#endif

    // Do we continue processing?
    return Application::Update(deltaTime);
}

void GameApplication::Render()
{
    Application::Render();

#if GAME_LOGGING_VERBOSITY_FULL
    MurphEngine::Log::LogToFile("Love2Murph Render");
#endif
}

void GameApplication::ApplicationShutdown()
{
    MurphEngine::Log::LogToFile("Love2Murph Shutdown");
    Application::ApplicationShutdown();
}

