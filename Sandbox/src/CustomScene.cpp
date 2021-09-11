#pragma once
#include "../headers/CustomScene.h"

CustomScene::BoxShape::BoxShape()
	: SFENG::Component(), m_Trans(nullptr), rb(nullptr)
{

}

bool CustomScene::BoxShape::Init()
{
	m_Trans = &this->entity->GetCopmonent<SFENG::Transform>();
	m_Shape.setSize(m_Trans->size);
	m_Shape.setOrigin(m_Trans->size / 2.0f);
	m_Shape.setPosition(m_Trans->position);
	m_Shape.setFillColor(sf::Color::Black);
	rb = &this->entity->GetCopmonent<SFENG::RigidBody2D>();
	return Component::Init();
}

void CustomScene::BoxShape::Update(const sf::Time&)
{
}

void CustomScene::BoxShape::FixedUpdate(const sf::Time& elapsed)
{
	this->m_Shape.setSize(m_Trans->size);
	this->m_Shape.setPosition(m_Trans->position);
	this->m_Shape.setRotation(m_Trans->angle * 180.0f / M_PI);
}

void CustomScene::BoxShape::Draw(sf::RenderWindow& window)
{
	window.draw(m_Shape);
}

CustomScene::CircleShape::CircleShape()
	: SFENG::Component(), m_Trans(nullptr), rb(nullptr)
{

}

bool CustomScene::CircleShape::Init()
{
	m_Trans = &this->entity->GetCopmonent<SFENG::Transform>();
	m_Shape.setRadius(m_Trans->size.x);
	m_Shape.setOrigin(m_Trans->size.x, m_Trans->size.x);
	m_Shape.setPosition(m_Trans->position);
	m_Shape.setFillColor(sf::Color::Red);
	rb = &this->entity->GetCopmonent<SFENG::RigidBody2D>();
	return Component::Init();
}

void CustomScene::CircleShape::Update(const sf::Time&)
{
}

void CustomScene::CircleShape::FixedUpdate(const sf::Time& elapsed)
{
	m_Shape.setRadius(m_Trans->size.x);
	this->m_Shape.setPosition(m_Trans->position);
	this->m_Shape.setRotation(m_Trans->angle);
}

void CustomScene::CircleShape::Draw(sf::RenderWindow& window)
{
	window.draw(m_Shape);
}


CustomScene::CustomScene(SFENG::Engine& engine, b2World& world)
	: SFENG::Scene(engine, world)
{
	Main();
	AddSprite();
	//AddCanvas();
	//AddSelectBox();
	SFENG::UI::Canvas canvas("Canvas1", m_LCManager);
	{
		std::string textBoxName = canvas.AddElement("Test TextBox", SFENG::UI::UIElementType::TextBox);
		SFENG::UI::Textbox* txtBox = dynamic_cast<SFENG::UI::Textbox*>(canvas.GetElement(textBoxName));
		txtBox->entity->GetCopmonent<SFENG::Transform>().position = Vec2f(300.0f, 400.0f);
		SFENG::UI::TextEnterHandler* txtHandler = &txtBox->entity->GetCopmonent<SFENG::UI::TextEnterHandler>();
		txtHandler->SetBoxColor(sf::Color::Red);
		txtHandler->SetCharacterSize(25);
		txtHandler->SetMaxNumOfChars(60);
		txtHandler->SetTextColor(sf::Color::Green);
	}
	{
		std::string textBoxName = canvas.AddElement("Test TextBox", SFENG::UI::UIElementType::TextBox);
		SFENG::UI::Textbox* txtBox = dynamic_cast<SFENG::UI::Textbox*>(canvas.GetElement(textBoxName));
		txtBox->entity->GetCopmonent<SFENG::Transform>().position = Vec2f(300.0f, 100.0f);
		txtBox->entity->GetCopmonent<SFENG::Transform>().size = Vec2f(150.0f, 25.0f);
		SFENG::UI::TextEnterHandler* txtHandler = &txtBox->entity->GetCopmonent<SFENG::UI::TextEnterHandler>();
		txtHandler->SetBoxColor(sf::Color::Blue);
		txtHandler->SetCharacterSize(16);
		txtHandler->SetMaxNumOfChars(60);
		txtHandler->SetTextColor(sf::Color::Black);
	}
}

void CustomScene::Main()
{
	AddBox("Ground", Vec2f(400.0f, 600.0f), Vec2f(1200.f, 50.0f), b2BodyType::b2_staticBody);
	std::mt19937 random(time(0));
	std::uniform_real_distribution<float> xPos(100.0f, 500.0f);
	std::uniform_real_distribution<float> yPos(100.0f, 300.0f);
	for (int i = 0; i < 100; i++) {
		AddBox("Box" + std::to_string(i), Vec2f(xPos(random), yPos(random)), { 10.0f , 10.0f }, b2BodyType::b2_dynamicBody);
		AddCircle("Circle" + std::to_string(i), Vec2f(xPos(random), yPos(random)), 10.0f, b2BodyType::b2_dynamicBody);
	}
}

void CustomScene::AddSelectBox()
{
	SFENG::Entity* selectBox = this->m_LCManager.CreateEntity("SelectBox");
	SFENG::Highlightable* boxShape = &selectBox->AddComponent<SFENG::Highlightable>();
	boxShape->ListenToKeys(true);
	OnClick* clk = &selectBox->AddComponent<OnClick>();
	SFENG::Transform& trans = selectBox->GetCopmonent<SFENG::Transform>();
	trans.position = Vec2f(350.0f, 200.0f);
	trans.size = Vec2f(150.0f, 150.0f);
}

void CustomScene::AddSprite()
{
	SFENG::ResourceManager::AddTexture("SampleSprite.png", "Sample");
	SFENG::Entity* en = this->m_LCManager.CreateEntity("Entity");
	SFENG::Transform& transform = en->GetCopmonent<SFENG::Transform>();
	transform.position = { 200.0f, 200.0f };
	transform.size = { 32.0f, 32.0f };
	SFENG::SpriteRenderer& sr = en->AddComponent<SFENG::SpriteRenderer>();
	SFENG::Animator& animator = en->AddComponent<SFENG::Animator>();
	sr.AttachTexture("Sample");
	SFENG::Animation* IDLEAnimation = animator.AddAnimation("IDLE");
	sf::Time delay = sf::seconds(0.15f);
	sf::IntRect rect = { 0, 0, 32, 32 };
	IDLEAnimation->AddFrame(rect, delay);
	rect.left = 32;
	IDLEAnimation->AddFrame(rect, delay);
	rect.left = 64;
	IDLEAnimation->AddFrame(rect, delay);
	rect.left = 96;
	IDLEAnimation->AddFrame(rect, delay);
	rect.left = 64;
	IDLEAnimation->AddFrame(rect, delay);
	rect.left = 32;
	IDLEAnimation->AddFrame(rect, delay);
	animator.SetActiveAnimation("IDLE");
	IDLEAnimation->Loop(true);
}

void CustomScene::AddCanvas()
{
	SFENG::UI::Canvas canvas("Canvas1", m_LCManager);
	std::string textBoxName = canvas.AddElement("Test TextBox", SFENG::UI::UIElementType::TextBox);
	SFENG::UI::Textbox* txtBox = dynamic_cast<SFENG::UI::Textbox*>(canvas.GetElement(textBoxName));
	txtBox->entity->GetCopmonent<SFENG::Transform>().position = Vec2f(300.0f, 400.0f);
	SFENG::UI::TextEnterHandler* txtHandler = &txtBox->entity->GetCopmonent<SFENG::UI::TextEnterHandler>();
	txtHandler->SetBoxColor(sf::Color::Red);
	txtHandler->SetCharacterSize(25);
	txtHandler->SetMaxNumOfChars(60);
	txtHandler->SetTextColor(sf::Color::Green);

}

void CustomScene::AddBox(const std::string& name, const Vec2f& position, const Vec2f& size, b2BodyType type)
{
	SFENG::Entity* newEntity = m_LCManager.CreateEntity(name);
	m_Entities[name] = newEntity;
	SFENG::Transform& trans = newEntity->GetCopmonent<SFENG::Transform>();
	trans.size = size;
	trans.position = position;
	SFENG::RigidBody2D& rb = newEntity->AddComponent<SFENG::RigidBody2D>(&this->m_PhysicsWorld);
	SFENG::BoxCollider& boxCol = newEntity->AddComponent<SFENG::BoxCollider>(&this->m_PhysicsWorld);
	BoxShape& shape = newEntity->AddComponent<BoxShape>();
	rb.SetBodyType(type);
}

void CustomScene::AddCircle(const std::string& name, const Vec2f& position, float radius, b2BodyType type)
{
	SFENG::Entity* newEntity = m_LCManager.CreateEntity(name);
	m_Entities[name] = newEntity;
	SFENG::Transform& trans = newEntity->GetCopmonent<SFENG::Transform>();
	trans.size = { radius , radius };
	trans.position = position;
	SFENG::RigidBody2D& rb = newEntity->AddComponent<SFENG::RigidBody2D>(&this->m_PhysicsWorld);
	SFENG::CircleCollider& boxCol = newEntity->AddComponent<SFENG::CircleCollider>(&this->m_PhysicsWorld);
	CircleShape& shape = newEntity->AddComponent<CircleShape>();
	rb.SetBodyType(type);
}
