#pragma once
#include "IComponent.h"

namespace MurphEngine
{
    class AIComponent final :
        public IComponent
    {
        virtual void Initialize() override;
        virtual void Render() override;
        virtual void Shutdown() override;

    public:
        AIComponent(IActor* ownerActor);
    };

}