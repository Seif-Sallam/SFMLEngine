#pragma once
#include "PCH.h"

class LevelScene : public SFENG::Scene
{
public:
    //Do the initialization in the scene and that is it
    LevelScene(SFENG::Engine &engine);
    ~LevelScene();

private:
    void AddMain();

    std::map<std::string, SFENG::Entity *> m_Entities;
};