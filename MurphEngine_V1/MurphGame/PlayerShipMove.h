#pragma once
#include "../MurphEngine/InputComponent.h"


class PlayerShipMove final :
    public MurphEngine::InputComponent
{
public:
    PlayerShipMove(MurphEngine::IActor* pOwner);

    virtual void Update([[maybe_unused]] double deltaTime) override;
};

