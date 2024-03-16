#pragma once
#include "DynamicCollider.h"

namespace MurphEngine
{

    class PlayerCollider :
        public DynamicCollider
    {
    public:
        PlayerCollider(IActor* pOwner);
        virtual void Initialize() override;
        virtual void Update([[maybe_unused]] double deltaTime) override;
    };

}
