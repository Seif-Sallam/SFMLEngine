#include "../headers/LevelScene.h"
#include "../headers/Prefabs/SpaceShip.h"
LevelScene::LevelScene(SFENG::Engine &engine)
    : Scene(engine)
{
    AddMain();
}

LevelScene::~LevelScene()
{
}

void LevelScene::AddMain()
{

    {
        SFENG::ResourceManager::AddTexture("rsc/textures/background0.jpg", "Background");
        SFENG::Entity *background = m_LCManager.CreateEntity("Background");
        auto &sp = background->AddComponent<SFENG::SpriteRenderer>();
        sp.AttachTexture("Background");
        auto &trans = background->GetComponent<SFENG::Transform>();
        Vec2u windowSize = m_Engine.GetWindow().getSize();
        SFENG::Engine::GetWindow().setTitle("Astroids");
        trans.position = Vec2f(windowSize.x / 2.f, windowSize.y / 2.f);
    }

    SpaceShip player(m_LCManager.CreateEntity("Player"));
}