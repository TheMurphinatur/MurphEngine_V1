#include "pch.h"
#include "AIComponent.h"

void MurphEngine::AIComponent::Initialize()
{
}


void MurphEngine::AIComponent::Render()
{
}

void MurphEngine::AIComponent::Shutdown()
{
}

MurphEngine::AIComponent::AIComponent(IActor* ownerActor)
{
    m_pOwnerActor = ownerActor;
}
