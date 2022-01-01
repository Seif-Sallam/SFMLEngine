#include "../headers/PhysicsListener.h"

namespace SFENG
{
    PhysicsListener::PhysicsListener()
    {
    }
    void PhysicsListener::BeginContact(b2Contact *contact)
    {
        b2Fixture *fixtureA = contact->GetFixtureA();
        b2Fixture *fixtureB = contact->GetFixtureB();

        b2Body *bodyA = fixtureA->GetBody();
        b2Body *bodyB = fixtureB->GetBody();

        auto dataA = bodyA->GetUserData();
        auto dataB = bodyB->GetUserData();
        Entity *entityA = reinterpret_cast<Entity *>(dataA.pointer);
        Entity *entityB = reinterpret_cast<Entity *>(dataB.pointer);
        m_ContactedEntities.push_back(std::make_pair(entityA, entityB));

        std::cout << "Entity: " << entityA->GetName() << " , was in contact with: " << entityB->GetName() << std::endl;
    }

    void PhysicsListener::Update()
    {
        m_ContactedEntities.clear();
    }

    PhysicsListener::~PhysicsListener()
    {
        m_ContactedEntities.clear();
    }

    const std::list<std::pair<Entity *, Entity *>> &PhysicsListener::GetContactList() const
    {
        return m_ContactedEntities;
    }
}