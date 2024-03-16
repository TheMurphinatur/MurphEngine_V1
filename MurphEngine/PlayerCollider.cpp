#include "PlayerCollider.h"

#include <box2d/b2_body.h>
#include <box2d/b2_world.h>

#include "ResourceManager.h"

MurphEngine::PlayerCollider::PlayerCollider(IActor* pOwner)
    : DynamicCollider(pOwner)
{
    m_id = "PlayerCollider";
}



void MurphEngine::PlayerCollider::Initialize()
{
    DynamicCollider::Initialize();
}


void MurphEngine::PlayerCollider::Update([[maybe_unused]] double deltaTime)
{
    DynamicCollider::Update(deltaTime);
}
