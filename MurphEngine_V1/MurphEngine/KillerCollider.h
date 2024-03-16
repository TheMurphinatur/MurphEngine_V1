#pragma once
#include "DynamicCollider.h"
namespace MurphEngine
{
    
class KillerCollider final :
    public DynamicCollider
{
    std::string m_textReference;

public:
    KillerCollider(IActor* pOwner);
    virtual void Render() override;
    virtual void Shutdown() override;

    virtual void HandleCollisionEvent(Message collisionEvent, IActor* pActor, IActor* OtherActor) override;
};

}
