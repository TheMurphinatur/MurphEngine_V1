#include "pch.h"
#include "WindowsSystem.h"
#include <Windows.h>

#include <cassert>

#include "MurphKeyboard.h"
#include "ResourceManager.h"
#include "Bleach_New/BleachNew.h"


MurphEngine::WindowsSystem::WindowsSystem()
{
    m_pGraphics = BLEACH_NEW(IGraphics());
    m_keyboard = BLEACH_NEW(MurphKeyboard());
    m_pResourceManager = BLEACH_NEW(ResourceManager(this));
}

MurphEngine::WindowsSystem::~WindowsSystem()
{
    BLEACH_DELETE(m_keyboard);
    m_keyboard = nullptr;
    m_pGraphics->ShutDownGraphics();
    BLEACH_DELETE(m_pGraphics);
    m_pGraphics = nullptr;

    m_pResourceManager->ShutDown();
    BLEACH_DELETE(m_pResourceManager);
    m_pResourceManager = nullptr;
}

void MurphEngine::WindowsSystem::CreateSystemWindow(const char* title, int locationX, int locationY, int width,
    int height)
{
    m_windowWidth = width;
    m_windowHeight = height;
    m_pWindow = SDL_CreateWindow(title, locationX, locationY, m_windowWidth, m_windowHeight, 0);
    m_pGraphics->CreateRenderer(m_pWindow, 50, 50, 50, 255);
}

void MurphEngine::WindowsSystem::Initialize()
{
    int error = SDL_Init(SDL_INIT_TIMER | SDL_INIT_EVENTS);
    if (error == 0) // everything initialized without issue.
    {
        Log::LogToFile("SDL_Init succeeded.");
    }
    else // if there was an issue, we state the error, and return a fail code.
    {
        Log::LogToFile("STD_init failed to initialize with error code: ");
        Log::LogToFile(SDL_GetError());
    }

    m_pResourceManager->Initialize();
}

void MurphEngine::WindowsSystem::SystemShutDown()
{
    SDL_Quit();
    Log::LogToFile("SDL Quit called.");

    Log::EndLogging(); //close the log file on engine shutdown
}

bool MurphEngine::WindowsSystem::ProcessEvents([[maybe_unused]]double deltaTime)
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_WINDOWEVENT:
            if (event.window.event == SDL_WINDOWEVENT_CLOSE)
            {
                Log::LogToConsole("Window Closed.");
                return false;
            }
            break;

        case SDL_KEYDOWN:
            SDL_Keycode SDL_keyPressed;
            SDL_keyPressed = event.key.keysym.sym;
            m_keyboard->OnSDLKeyboardPress(SDL_keyPressed);

            // if the player pressed escape to quit.
            if (m_keyboard->IsKeyPressed(MurphKeyboard::MurphKeys::MurphKey_esc))
            {
                return false;
            }
            break;

        case SDL_KEYUP:
            SDL_keyPressed = event.key.keysym.sym;
            m_keyboard->OnSDLKeyRelease(SDL_keyPressed);
            break;

        default:
            break;
        }
    }
    return true;
}
