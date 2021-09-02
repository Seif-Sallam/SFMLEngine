#include "..\headers\CustomGame.h"

CustomGame::CustomGame()
	: SFENG::Engine()
{
	//this->GetWindow().setVerticalSyncEnabled(false);
	this->SFENG::Engine::PushStartingScene(std::make_unique<CustomScene>(*this, *m_PhysicsWorld));
}

CustomGame::~CustomGame()
{
}

void CustomGame::HandleScenes()
{
}
