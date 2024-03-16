#pragma once

#include "../MurphEngine/Application.h"

class GameApplication final : public MurphEngine::Application
{

protected:
    virtual void ApplicationInitialize() override;

    virtual bool Update(double deltaTime) override;
    virtual void Render() override;

    virtual void ApplicationShutdown() override;
public:
    virtual ~GameApplication() override = default;

};
