#pragma once


//#include "Logging.h"
#include "IWindow.h"
#include "IGraphics.h"
#include "MurphKeyboard.h"
#include "PhysicsManager.h"

#define WINDOWS 1

#define SYSTEM WINDOWS


namespace MurphEngine
{
    class ResourceManager;
    // Move actual functionality into a WindowsSystem subclass.
            // WindowsSystem
            // iKeyboard
                // MurphKeyboard (sdl wrapper)
            // iMouse
                // MurphMouse
    class ISystem
    {
    protected:
        ISystem* m_pSystem = nullptr;
        SDL_Window* m_pWindow = nullptr;
        IGraphics* m_pGraphics = nullptr;
        MurphKeyboard* m_keyboard = nullptr;
        ResourceManager* m_pResourceManager = nullptr; //TODO: Tie in resource manager
        int m_windowWidth = 0;
        int m_windowHeight = 0;

    public:

        ISystem() = default;
        virtual ~ISystem() = default;


        //static ISystem* CreateSystem();
        virtual void CreateSystemWindow(const char* title, int locationX, int locationY, int width, int height) = 0;
        virtual void Initialize() = 0;
        virtual void StartDrawing() = 0;
        virtual void PresentGraphics() = 0;
        virtual bool ProcessEvents(double deltaTime) = 0;
        virtual ISystem* GetSystem() = 0;
        virtual IGraphics* GetGraphics() = 0;
        virtual ResourceManager* GetResourceManager() = 0;
        virtual const char* GetName() { return "iSystem"; }
        MurphKeyboard* GetKeyboard() const { return m_keyboard; }
        int GetWindowHeight() const { return m_windowHeight; }
        int GetWindowWidth() const { return m_windowWidth; }

        virtual void SystemShutDown() = 0;
    };

}