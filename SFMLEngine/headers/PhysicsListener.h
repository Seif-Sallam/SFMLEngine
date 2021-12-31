#pragma once
#include <iostream>
#include <list>
#include "box2d/box2d.h"
#include "Entity.h"
#include "box2d/b2_world_callbacks.h"

namespace SFENG
{
    class PhysicsListener : public b2ContactListener
    {
    public:
        PhysicsListener();
        void BeginContact(b2Contact *contact) override;
        const std::list<std::pair<Entity *, Entity *>> &GetContactList() const;
        void Update();
        ~PhysicsListener();

    private:
        std::list<std::pair<Entity *, Entity *>> m_ContactedEntities;
    };
}