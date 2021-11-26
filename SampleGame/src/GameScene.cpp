#include "GameScene.h"
#include "Components/PlayerController.h"

GameScene::GameScene(SFENG::Engine& engine)
: SFENG::Scene(engine)
{
	SFENG::Entity* player = m_LCManager.CreateEntity("Player");
	
	auto& controller = player->AddComponent<SFENG::Controller>();
	auto& playerController = player->AddComponent<PlayerController>();
	auto& sp = player->AddComponent<SFENG::SpriteRenderer>();
	auto& bc = player->AddComponent<SFENG::BoxCollider>();
	SFENG::ResourceManager::AddTexture("rsc/white_king.png", "Texture");
	sf::Shader* shader = new sf::Shader;
	shader->loadFromFile("rsc/shaders/VertexShader.glsl", "rsc/shaders/FragmentShader.glsl");
	sp.AttachTexture("Texture");
	sf::RenderStates* state = new sf::RenderStates;
	shader->setUniform("texture", sf::Shader::CurrentTexture);
	state->texture = &SFENG::ResourceManager::GetTextrue("Texture");
	state->shader = shader;
	sp.SetRenderState(*state);
	
	playerController.speed = 100.f;

}