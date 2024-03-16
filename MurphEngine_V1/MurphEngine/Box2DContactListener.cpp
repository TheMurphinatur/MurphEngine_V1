#include "Box2DContactListener.h"

#include <box2d/b2_contact.h>

void MurphEngine::Box2DContactListener::ClearResults()
{
    m_beginContact.clear();
    m_endContact.clear();
}

void MurphEngine::Box2DContactListener::BeginContact(b2Contact* pContact)
{
    Contact contact;
    contact.pFixtureA = pContact->GetFixtureA();
    contact.pFixtureB = pContact->GetFixtureB();
    m_beginContact.push_back(contact);
}

void MurphEngine::Box2DContactListener::EndContact(b2Contact* pContact)
{
    Contact contact;
    contact.pFixtureA = pContact->GetFixtureA();
    contact.pFixtureB = pContact->GetFixtureB();
    m_endContact.push_back(contact);
}
