#include "pch.h"
#include "IGraphics.h"

#include <SDL_image.h>

MurphEngine::IGraphics::IGraphics()
    : m_pRenderer(nullptr)
{
    InitializeGraphics();
}

MurphEngine::IGraphics::~IGraphics()
{
}

void MurphEngine::IGraphics::InitializeGraphics()
{
    int error = SDL_Init(SDL_INIT_VIDEO);
    if (error != 0)
    {
        Log::LogToConsole("SDL Video Initialization Failed.");
    }
    else
        Log::LogToConsole("SDL Video Initialized Successfully!");

}


/**
 * \brief Create renderer within targeted window with given background color 
 * \param pWindow Window to render to
 * \param r red value
 * \param g green value
 * \param b blue value
 * \param a alpha value
 */
void MurphEngine::IGraphics::CreateRenderer(SDL_Window* pWindow, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    m_pRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED);
    if (m_pRenderer != nullptr)
    {
        Log::LogToFile("Renderer created successfully.");
    }
    else
    {
        Log::LogToFile("Renderer Creation Failed");
        Log::LogToFile(SDL_GetError());
        SDL_Quit();
    }

    // Set the background to a white background.
    SetDrawColor(r, g, b, a); // TODO: move this
    //execute the clear
    //StartDrawing(); //TODO: Delete this
    
}

void MurphEngine::IGraphics::SetDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) const
{
    SDL_SetRenderDrawColor(m_pRenderer, r,
        g, b, a);
}

void MurphEngine::IGraphics::ShutDownGraphics() const
{
    SDL_DestroyRenderer(m_pRenderer);
}

SDL_Texture* MurphEngine::IGraphics::LoadTexture(const char* filename) const
{
    SDL_Surface* temp = IMG_Load(filename);
    if (temp == nullptr)
    {
        std::cout << "Texture failed to load image:" << filename << ". Error:" << SDL_GetError() << std::endl;
    }
    //Creating a texture from temp surface above.


    SDL_Texture* texture = SDL_CreateTextureFromSurface(m_pRenderer, temp);
    if (texture == nullptr)
    {
        std::cout << "Texture failed to load. Error: " << SDL_GetError() << std::endl;
    }

    //clear the surface
    SDL_FreeSurface(temp);

    return texture;
}
