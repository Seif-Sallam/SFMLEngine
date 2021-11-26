#include "Game.h"
#include "GameScene.h"
Game::Game()
	: SFENG::Engine()
{
	PushStartingScene(std::make_unique<GameScene>(*this));

}

Game::~Game()
{

}

void Game::HandleScenes()
{
	
}