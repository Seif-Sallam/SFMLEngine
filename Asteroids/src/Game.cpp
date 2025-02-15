#include "Game.h"
#include "LevelScene.h"

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
