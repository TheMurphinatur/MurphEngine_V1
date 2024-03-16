#pragma once
#include "ISystem.h"
//#include "MurphKeyboard.h"




namespace MurphEngine
{

    class WindowsSystem :
        public ISystem
    {

    public:
        void SetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
        void CreateSystemWindow(const char* title, int locationX, int locationY, int width, int height) override;
        void Initialize() override;
        const char* GetName() override { return "Windows System"; }
        IGraphics* GetGraphics() override { return m_pGraphics; }
        virtual ISystem* GetSystem() override { return m_pSystem; }
        virtual ResourceManager* GetResourceManager() override { return m_pResourceManager; }


        WindowsSystem();
        virtual ~WindowsSystem() override;
        void SystemShutDown() override;
        bool ProcessEvents([[maybe_unused]]double deltaTime) override;
        void StartDrawing() override { m_pGraphics->StartDrawing(); }
        void PresentGraphics() override { m_pGraphics->EndDrawing(); }
    };


}
