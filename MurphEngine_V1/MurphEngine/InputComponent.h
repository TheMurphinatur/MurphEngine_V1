#pragma once
#include "MovementComponent.h"

namespace MurphEngine
{
    
class InputComponent:
 public MovementComponent
{
public:
    InputComponent(IActor* pOwner);
    virtual void Initialize() override;
    virtual void Update([[maybe_unused]] double deltaTime) override;
};

}
