#pragma once
#include "IComponent.h"

namespace MurphEngine
{

    class ProjectileGenerationComponent :
        public IComponent
    {
    public:
        virtual void Update([[maybe_unused]]double deltaTime) override { }
        virtual void Initialize() override { }
    };

}

