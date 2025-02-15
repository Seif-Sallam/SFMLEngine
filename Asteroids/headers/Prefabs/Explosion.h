#pragma once
#include "PCH.h"

class Explosion
{
public:
    Explosion(SFENG::Entity *createdEntity, const Vec2f &position);
    SFENG::Entity *entity;
};