#pragma once
#include <SDL.h>
#include "Logging.h"


namespace MurphEngine
{

    class IWindow
    {



        SDL_Window* m_pWindow;
    public:
        IWindow();
        virtual ~IWindow();
        virtual void Initialize();
        virtual void ProcessEvents() { }

        virtual void MinimizeScreen() { }
        virtual void MaximizeScreen() { }
        virtual void FullScreen() { }

        virtual void CloseWindow() { }

        SDL_Window* GetSDLWindow() const { return m_pWindow; } // Dont return SDL window. return IWin
        IWindow* GetWindow() { return this; } //IWindow;}
        // push into SDLWindow.

        //GAME CODE CANNOT REFERENCE SDL_Code.
    };

}
