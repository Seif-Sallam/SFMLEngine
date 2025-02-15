#include "CustomScene.h"

CustomScene::ViewModifier::ViewModifier(sf::View &view)
	: m_View(view)
{
}
void CustomScene::ViewModifier::Update(const sf::Time &elapsed)
{
	if (SFENG::Keyboard::IsKeyPressed(sf::Keyboard::Left))
	{
		m_View.move(-250.f * elapsed.asSeconds(), 0.f);
	}
	if (SFENG::Keyboard::IsKeyPressed(sf::Keyboard::Right))
	{
		m_View.move(250.f * elapsed.asSeconds(), 0.f);
	}
	if (SFENG::Keyboard::IsKeyPressed(sf::Keyboard::Up))
	{
		m_View.move(0.f, -250.f * elapsed.asSeconds());
	}
	if (SFENG::Keyboard::IsKeyPressed(sf::Keyboard::Down))
	{
		m_View.move(0.f, 250.f * elapsed.asSeconds());
	}
}
void CustomScene::ViewModifier::Draw(sf::RenderWindow &window)
{
	window.setView(m_View);
}

CustomScene::BoxShape::BoxShape()
	: SFENG::Component(), m_Trans(nullptr), rb(nullptr)
{
}

bool CustomScene::BoxShape::Init()
{
	m_Trans = &this->entity->GetComponent<SFENG::Transform>();
	m_Shape.setSize(m_Trans->size);
	m_Shape.setOrigin(m_Trans->size / 2.0f);
	m_Shape.setPosition(m_Trans->position);
	m_Shape.setFillColor(sf::Color::Black);
	// rb = &this->entity->GetComponent<SFENG::RigidBody2D>();
	return Component::Init();
}

void CustomScene::BoxShape::Update(const sf::Time &)
{
}

void CustomScene::BoxShape::FixedUpdate(const sf::Time &elapsed)
{
	this->m_Shape.setSize(m_Trans->size);
	this->m_Shape.setPosition(m_Trans->position);
	this->m_Shape.setRotation(m_Trans->angle);
}

void CustomScene::BoxShape::Draw(sf::RenderWindow &window)
{
	window.draw(m_Shape);
}

CustomScene::CircleShape::CircleShape()
	: SFENG::Component(), m_Trans(nullptr), rb(nullptr)
{
}

bool CustomScene::CircleShape::Init()
{
	m_Trans = &this->entity->GetComponent<SFENG::Transform>();
	m_Shape.setRadius(m_Trans->size.x);
	m_Shape.setOrigin(m_Trans->size.x, m_Trans->size.x);
	m_Shape.setPosition(m_Trans->position);
	m_Shape.setFillColor(sf::Color::Red);
	rb = &this->entity->GetComponent<SFENG::RigidBody2D>();
	return Component::Init();
}

void CustomScene::CircleShape::Update(const sf::Time &)
{
}

void CustomScene::CircleShape::FixedUpdate(const sf::Time &elapsed)
{
	this->m_Shape.setRadius(m_Trans->size.x);
	this->m_Shape.setPosition(m_Trans->position);
	this->m_Shape.setRotation(m_Trans->angle);
}

void CustomScene::CircleShape::Draw(sf::RenderWindow &window)
{
	window.draw(m_Shape);
}

CustomScene::CustomScene(SFENG::Engine &engine)
	: SFENG::Scene(engine, true)
{
	engine.SetGravity(Vec2f(0.f, 9.8f));
	m_LCManager.CreateEntity("ViewModifier")->AddComponent<ViewModifier>(this->m_Engine.engineView);
	Main();
	// AddSprite();
	// AddCanvas();
	// AddSelectBox();
	// SFENG::UI::Canvas canvas("Canvas1", m_LCManager);
	// {
	// 	std::string textBoxName = canvas.AddElement("Test TextBox", SFENG::UI::UIElementType::TextBox);
	// 	SFENG::UI::Textbox *txtBox = dynamic_cast<SFENG::UI::Textbox *>(canvas.GetElement(textBoxName));
	// 	txtBox->entity->GetComponent<SFENG::Transform>().position = Vec2f(300.0f, 400.0f);
	// 	SFENG::UI::TextEnterHandler *txtHandler = &txtBox->entity->GetComponent<SFENG::UI::TextEnterHandler>();
	// 	txtHandler->SetBoxColor(sf::Color::Red);
	// 	txtHandler->SetCharacterSize(25);
	// 	txtHandler->SetMaxNumOfChars(60);
	// 	txtHandler->SetTextColor(sf::Color::Green);
	// }
	// {
	// 	std::string textBoxName = canvas.AddElement("Test TextBox", SFENG::UI::UIElementType::TextBox);
	// 	SFENG::UI::Textbox *txtBox = dynamic_cast<SFENG::UI::Textbox *>(canvas.GetElement(textBoxName));
	// 	txtBox->entity->GetComponent<SFENG::Transform>().position = Vec2f(300.0f, 100.0f);
	// 	txtBox->entity->GetComponent<SFENG::Transform>().size = Vec2f(150.0f, 25.0f);
	// 	SFENG::UI::TextEnterHandler *txtHandler = &txtBox->entity->GetComponent<SFENG::UI::TextEnterHandler>();
	// 	txtHandler->SetBoxColor(sf::Color::Blue);
	// 	txtHandler->SetCharacterSize(16);
	// 	txtHandler->SetMaxNumOfChars(60);
	// 	txtHandler->SetTextColor(sf::Color::Black);
	// }
}

void CustomScene::Main()
{
	const int boxNum = 100;

	AddBox("Ground", Vec2f(400.0f, 600.0f), Vec2f(1200.f, 50.0f), b2BodyType::b2_staticBody);
	std::mt19937 random(time(0));
	std::uniform_real_distribution<float> xPos(100.0f, 500.0f);
	std::uniform_real_distribution<float> yPos(100.0f, 300.0f);
	for (int i = 0; i < boxNum; i++)
	{
		AddBox("Box" + std::to_string(i), Vec2f(xPos(random), yPos(random)), {15.0f, 15.0f}, b2BodyType::b2_dynamicBody);
		AddCircle("Circle" + std::to_string(i), Vec2f(xPos(random), yPos(random)), 15.0f, b2BodyType::b2_dynamicBody);
	}

	SFENG::Entity *newEntity = m_LCManager.CreateEntity("Movable Box");
	newEntity->SetTag("Movable Box");
	m_Entities["Movable Box"] = newEntity;
	SFENG::Transform &trans = newEntity->GetComponent<SFENG::Transform>();
	trans.size = Vec2f(50.0f, 50.0f);
	trans.position = Vec2f(0.0f, 0.0f);
	SFENG::RigidBody2D &rb = newEntity->AddComponent<SFENG::RigidBody2D>();
	SFENG::BoxCollider &boxCol = newEntity->AddComponent<SFENG::BoxCollider>();
	BoxShape &shape = newEntity->AddComponent<BoxShape>();
	rb.SetBodyType(b2_staticBody);
	newEntity->AddComponent<CollisionDetector>();
	SFENG::Controller *controller = &newEntity->AddComponent<SFENG::Controller>();
	controller->SetBoxCollider(&boxCol);
	auto boxCon = &newEntity->AddComponent<BoxController>();
	boxCon->SetController(controller);
}

void CustomScene::AddSelectBox()
{
	SFENG::Entity *selectBox = this->m_LCManager.CreateEntity("SelectBox");
	SFENG::Highlightable *boxShape = &selectBox->AddComponent<SFENG::Highlightable>();
	boxShape->ListenToKeys(true);
	OnClick *clk = &selectBox->AddComponent<OnClick>();
	SFENG::Transform &trans = selectBox->GetComponent<SFENG::Transform>();
	trans.position = Vec2f(350.0f, 200.0f);
	trans.size = Vec2f(150.0f, 150.0f);
}

void CustomScene::AddSprite()
{
	SFENG::ResourceManager::AddTexture(RSC_DIR "SampleSprite.png", "Sample");
	SFENG::Entity *en = this->m_LCManager.CreateEntity("Entity");
	SFENG::Transform &transform = en->GetComponent<SFENG::Transform>();
	transform.position = {200.0f, 200.0f};
	transform.size = {32.0f, 32.0f};
	SFENG::SpriteRenderer &sr = en->AddComponent<SFENG::SpriteRenderer>();
	SFENG::Animator &animator = en->AddComponent<SFENG::Animator>();
	sr.AttachTexture("Sample");
	SFENG::Animation *IDLEAnimation = animator.AddAnimation("IDLE");
	sf::Time delay = sf::seconds(0.15f);
	sf::IntRect rect = {0, 0, 32, 32};
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
	SFENG::UI::Textbox *txtBox = dynamic_cast<SFENG::UI::Textbox *>(canvas.GetElement(textBoxName));
	txtBox->entity->GetComponent<SFENG::Transform>().position = Vec2f(300.0f, 400.0f);
	SFENG::UI::TextEnterHandler *txtHandler = &txtBox->entity->GetComponent<SFENG::UI::TextEnterHandler>();
	txtHandler->SetBoxColor(sf::Color::Red);
	txtHandler->SetCharacterSize(25);
	txtHandler->SetMaxNumOfChars(60);
	txtHandler->SetTextColor(sf::Color::Green);
}

void CustomScene::AddBox(const std::string &name, const Vec2f &position, const Vec2f &size, b2BodyType type)
{
	SFENG::Entity *newEntity = m_LCManager.CreateEntity(name);
	newEntity->SetTag("Box");
	m_Entities[name] = newEntity;
	SFENG::Transform &trans = newEntity->GetComponent<SFENG::Transform>();
	trans.size = size;
	trans.position = position;
	SFENG::RigidBody2D &rb = newEntity->AddComponent<SFENG::RigidBody2D>();
	SFENG::BoxCollider &boxCol = newEntity->AddComponent<SFENG::BoxCollider>();
	BoxShape &shape = newEntity->AddComponent<BoxShape>();
	rb.SetBodyType(type);
	// newEntity->AddComponent<CollisionDetector>();
}

void CustomScene::AddCircle(const std::string &name, const Vec2f &position, float radius, b2BodyType type)
{
	SFENG::Entity *newEntity = m_LCManager.CreateEntity(name);
	newEntity->SetTag("Circle");
	m_Entities[name] = newEntity;
	SFENG::Transform &trans = newEntity->GetComponent<SFENG::Transform>();
	trans.size = {radius, radius};
	trans.position = position;
	SFENG::RigidBody2D &rb = newEntity->AddComponent<SFENG::RigidBody2D>();
	SFENG::CircleCollider &boxCol = newEntity->AddComponent<SFENG::CircleCollider>();
	CircleShape &shape = newEntity->AddComponent<CircleShape>();
	rb.SetBodyType(type);
}
