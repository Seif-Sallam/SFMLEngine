#include "../headers/Game.h"
#include "../headers/LevelScene.h"

Game::Game()
{
    this->PushStartingScene(std::make_unique<LevelScene>(*this));
}

Game::~Game()
{
}

void Game::HandleScenes()
{
}
