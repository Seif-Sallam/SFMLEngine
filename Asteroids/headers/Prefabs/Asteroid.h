#pragma once
#include "PCH.h"
class AstroidController;
class Asteroid
{
public:
    Asteroid(SFENG::Entity *createdEntity, const Vec2f &position, const Vec2f &direction, bool big);
    SFENG::Entity *entity;
    bool IsAlive();

private:
    AstroidController *m_Controller;
};