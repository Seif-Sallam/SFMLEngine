#pragma once
#include "PCH.h"

class SpaceShip
{
public:
    SpaceShip(SFENG::Entity *createdEntity);
    SFENG::Entity *entity;

private:
    void SetAnimations();
    void SetPlayerController();

    SFENG::Animator *m_Animator;
};
