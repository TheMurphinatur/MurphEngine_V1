#include "pch.h"
#include "IWindow.h"



MurphEngine::IWindow::IWindow()
    : m_pWindow()
{
}

MurphEngine::IWindow::~IWindow()
{
    SDL_DestroyWindow(m_pWindow);
    Log::LogToFile("Closing window.");
}

void MurphEngine::IWindow::Initialize()
{
    m_pWindow = SDL_CreateWindow("test", 100, 100, 500, 500, static_cast<Uint32>(-1));
    if (m_pWindow == nullptr)
    {
        Log::LogToFile("Error Creating Window.");
        Log::LogToFile(SDL_GetError());

    }
    else
        Log::LogToFile("Window Created Successfully.");

}
