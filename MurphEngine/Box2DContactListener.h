#pragma once
#include <vector>

#include "Source/Middleware/box2d/b2_world_callbacks.h"



namespace MurphEngine
{
    
class Box2DContactListener :
    public b2ContactListener
{
public:
    struct Contact
    {
        b2Fixture* pFixtureA = nullptr;
        b2Fixture* pFixtureB = nullptr;
    };

private:
    std::vector<Contact> m_beginContact;
    std::vector<Contact> m_endContact;

public:
    virtual ~Box2DContactListener() override = default;

    std::vector<Contact>& GetBeginContacts() { return m_beginContact; }
    std::vector<Contact>& GetEndContacts() { return m_endContact; }

    void ClearResults();

    virtual void BeginContact(b2Contact* pContact) override;
    virtual void EndContact(b2Contact* pContact) override;

};

}
