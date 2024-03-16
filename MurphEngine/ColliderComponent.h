#pragma once
#include "IComponent.h"
namespace MurphEngine
{
    class ColliderComponent final :
        public IComponent
    {

    public:

        ColliderComponent(IActor* ownerActor);
    };

}