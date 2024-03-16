#pragma once
#include <SDL.h>

#include "Logging.h"

namespace MurphEngine
{

    class IGraphics
    {
        SDL_Renderer* m_pRenderer;

        public:

        ~IGraphics();
        IGraphics();
        static void InitializeGraphics();
        void CreateRenderer(SDL_Window* pWindow, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

        SDL_Renderer* GetRenderer() { return m_pRenderer; }


        void SetDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) const;
        void StartDrawing() const { SDL_RenderClear(m_pRenderer); }
        void EndDrawing() { SDL_RenderPresent(m_pRenderer);}
        void DrawLine(int x1, int y1, int x2, int y2) { SDL_RenderDrawLine(m_pRenderer, x1, y1, x2, y2); }
        void ShutDownGraphics() const;
        SDL_Texture* LoadTexture(const char* filename) const;

    private:
    };

}