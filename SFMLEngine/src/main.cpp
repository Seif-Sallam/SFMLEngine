//#include "ResourceManager.h"
//#include "Animation.h"
//#include "Keyboard.h"
//#include "FPSCounter.h"
//
//int main()
//{
//	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Works!");
//	window.setFramerateLimit(60);
//	window.setVerticalSyncEnabled(true);
//
//	sf::Text text;
//	sf::Font& font = SFENG::ResourceManager::Get().AddFont("rsc/Fonts/Alex_Bold.ttf", "something");
//	text.setFont(font);
//	text.setCharacterSize(24);
//	text.setPosition(Vec2f(0, 0));
//	text.setString("SOMETHING FONT");
//	sf::RectangleShape shape(sf::Vector2f(32, 32));
//	shape.setFillColor(sf::Color::White);
//	shape.setPosition(sf::Vector2f(100, 100));
//	sf::Texture& tex = SFENG::ResourceManager::Get().AddTexture("rsc/Textures/test.png", "test");
//	shape.setTexture(&tex);
//	bool inFocus = true;
//	sf::Texture& texture = SFENG::ResourceManager::Get().AddTexture("rsc/Textures/SampleSprite.png", "sample");
//	sf::Sprite sp;
//	sp.setTexture(texture);
//	sp.setPosition(Vec2f(300, 250));
//	SFENG::Animation anim(32, 32);
//	sf::Time delay = sf::seconds(0.15f);
//	anim.AddFrame(0, delay);
//	anim.AddFrame(1, delay);
//	anim.AddFrame(2, delay);
//	anim.AddFrame(3, delay);
//	anim.AddFrame(2, delay);
//	anim.AddFrame(1, delay);
//	anim.AddFrame(0, delay);
//
//
//	SFENG::FPSCounter FPS(&window);
//	sf::View view = window.getView();
//	while (window.isOpen())
//	{
//		sf::Event event;
//		while (window.pollEvent(event))
//		{
//			if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
//				window.close();
//			else if (event.type == sf::Event::LostFocus)
//				inFocus = false;
//			else if (event.type == sf::Event::GainedFocus)
//				inFocus = true;
//			SFENG::Keyboard::Update(event);
//		}
//
//		if (SFENG::Keyboard::IsKeyPressed(sf::Keyboard::Key::A))
//			view.move(-10.0f, 0.0f);
//		if (SFENG::Keyboard::IsKeyPressed(sf::Keyboard::Key::D))
//			view.move(10.0f, 0.f);
//		if (SFENG::Keyboard::IsKeyPressed(sf::Keyboard::Key::S))
//			view.move(0, 10.0f);
//		if (SFENG::Keyboard::IsKeyPressed(sf::Keyboard::Key::W))
//			view.move(0, -10.0f);
//
//
//		if (inFocus)
//		{
//			sp.setTextureRect(anim.GetFrame());
//			FPS.Update();
//
//			window.setView(view);
//			window.clear(sf::Color(192,168,128));
//			window.draw(text);
//			FPS.Draw();
//			window.draw(sp);
//			window.display();
//		}
//	}
//	SFENG::ResourceManager::Get().CleanUp();
//	return 0;
//}

int main()
{
	return 0;
}
// #include "PCH.h"

// class CustomScene : public SFENG::Scene
// {
// public:
// 	class BoxShape : public SFENG::Component
// 	{
// 	public:
// 		BoxShape();
// 		bool Init() override;
// 		void Update(const sf::Time &) override;
// 		void FixedUpdate(const sf::Time &elapsed) override;
// 		void Draw(sf::RenderWindow &window) override;

// 	private:
// 		sf::RectangleShape m_Shape;
// 		SFENG::Transform *m_Trans;
// 		SFENG::RigidBody2D *rb;
// 	};

// 	class CircleShape : public SFENG::Component
// 	{
// 	public:
// 		CircleShape();
// 		bool Init() override;
// 		void Update(const sf::Time &) override;
// 		void FixedUpdate(const sf::Time &elapsed) override;
// 		void Draw(sf::RenderWindow &window) override;

// 	private:
// 		sf::CircleShape m_Shape;
// 		SFENG::Transform *m_Trans;
// 		SFENG::RigidBody2D *rb;
// 	};

// 	class OnClick : public SFENG::Component
// 	{
// 	public:
// 		inline bool Init() override
// 		{
// 			m_Transform = &entity->GetComponent<SFENG::Transform>();
// 			if (entity->HasComponent<SFENG::Highlightable>())
// 				m_SE = &entity->GetComponent<SFENG::Highlightable>();
// 			else
// 				m_SE = nullptr;
// 			return SFENG::Component::Init();
// 		}
// 		inline void AttachSelectable(SFENG::Highlightable *se)
// 		{
// 			m_SE = se;
// 		}
// 		inline void Update(const sf::Time &time) override
// 		{
// 			shape.setSize(m_Transform->size);
// 			shape.setOrigin(m_Transform->size / 2.0f);
// 			shape.setPosition(m_Transform->position);
// 		}
// 		inline void HandleEvents(sf::Event &event) override
// 		{
// 			if (m_SE != nullptr)
// 			{
// 				if (m_SE->KeyPressed() == sf::Mouse::Button::Left)
// 				{
// 					std::cout << "Pressed\n";
// 				}
// 			}
// 			return SFENG::Component::HandleEvents(event);
// 		}
// 		inline void Draw(sf::RenderWindow &window) override
// 		{
// 			window.draw(shape);
// 			return SFENG::Component::Draw(window);
// 		}

// 	private:
// 		SFENG::Highlightable *m_SE;
// 		sf::RectangleShape shape;
// 		SFENG::Transform *m_Transform;
// 	};

// 	CustomScene(SFENG::Engine &engine);

// private:
// 	void Main();
// 	void AddSelectBox();
// 	void AddSprite();
// 	void AddCanvas();
// 	void AddBox(const std::string &name, const Vec2f &position, const Vec2f &size, b2BodyType type);
// 	void AddCircle(const std::string &name, const Vec2f &position, float radius, b2BodyType type);
// 	std::map<std::string, SFENG::Entity *> m_Entities;
// };

// class CustomGame : public SFENG::Engine
// {
// public:
// 	CustomGame();
// 	~CustomGame();
// 	void HandleScenes() override;

// private:
// };

// CustomGame::CustomGame()
// 	: SFENG::Engine()
// {
// 	//this->GetWindow().setVerticalSyncEnabled(false);
// 	this->SFENG::Engine::PushStartingScene(std::make_unique<CustomScene>(*this));
// }

// CustomGame::~CustomGame()
// {
// }

// void CustomGame::HandleScenes()
// {
// }

// CustomScene::BoxShape::BoxShape()
// 	: SFENG::Component(), m_Trans(nullptr), rb(nullptr)
// {
// }

// bool CustomScene::BoxShape::Init()
// {
// 	m_Trans = &this->entity->GetComponent<SFENG::Transform>();
// 	m_Shape.setSize(m_Trans->size);
// 	m_Shape.setOrigin(m_Trans->size / 2.0f);
// 	m_Shape.setPosition(m_Trans->position);
// 	m_Shape.setFillColor(sf::Color::Black);
// 	rb = &this->entity->GetComponent<SFENG::RigidBody2D>();
// 	return Component::Init();
// }

// void CustomScene::BoxShape::Update(const sf::Time &)
// {
// }

// void CustomScene::BoxShape::FixedUpdate(const sf::Time &elapsed)
// {
// 	this->m_Shape.setSize(m_Trans->size);
// 	this->m_Shape.setPosition(m_Trans->position);
// 	this->m_Shape.setRotation(m_Trans->angle);
// }

// void CustomScene::BoxShape::Draw(sf::RenderWindow &window)
// {
// 	window.draw(m_Shape);
// }

// CustomScene::CircleShape::CircleShape()
// 	: SFENG::Component(), m_Trans(nullptr), rb(nullptr)
// {
// }

// bool CustomScene::CircleShape::Init()
// {
// 	m_Trans = &this->entity->GetComponent<SFENG::Transform>();
// 	m_Shape.setRadius(m_Trans->size.x);
// 	m_Shape.setOrigin(m_Trans->size.x, m_Trans->size.x);
// 	m_Shape.setPosition(m_Trans->position);
// 	m_Shape.setFillColor(sf::Color::Red);
// 	rb = &this->entity->GetComponent<SFENG::RigidBody2D>();
// 	return Component::Init();
// }

// void CustomScene::CircleShape::Update(const sf::Time &)
// {
// }

// void CustomScene::CircleShape::FixedUpdate(const sf::Time &elapsed)
// {
// 	this->m_Shape.setRadius(m_Trans->size.x);
// 	this->m_Shape.setPosition(m_Trans->position);
// 	this->m_Shape.setRotation(m_Trans->angle);
// }

// void CustomScene::CircleShape::Draw(sf::RenderWindow &window)
// {
// 	window.draw(m_Shape);
// }

// CustomScene::CustomScene(SFENG::Engine &engine)
// 	: SFENG::Scene(engine)
// {
// 	Main();
// 	AddSprite();
// 	//AddCanvas();
// 	//AddSelectBox();
// 	SFENG::UI::Canvas canvas("Canvas1", m_LCManager);
// 	{
// 		std::string textBoxName = canvas.AddElement("Test TextBox", SFENG::UI::UIElementType::TextBox);
// 		SFENG::UI::Textbox *txtBox = dynamic_cast<SFENG::UI::Textbox *>(canvas.GetElement(textBoxName));
// 		txtBox->entity->GetComponent<SFENG::Transform>().position = Vec2f(300.0f, 400.0f);
// 		SFENG::UI::TextEnterHandler *txtHandler = &txtBox->entity->GetComponent<SFENG::UI::TextEnterHandler>();
// 		txtHandler->SetBoxColor(sf::Color::Red);
// 		txtHandler->SetCharacterSize(25);
// 		txtHandler->SetMaxNumOfChars(60);
// 		txtHandler->SetTextColor(sf::Color::Green);
// 	}
// 	{
// 		std::string textBoxName = canvas.AddElement("Test TextBox", SFENG::UI::UIElementType::TextBox);
// 		SFENG::UI::Textbox *txtBox = dynamic_cast<SFENG::UI::Textbox *>(canvas.GetElement(textBoxName));
// 		txtBox->entity->GetComponent<SFENG::Transform>().position = Vec2f(300.0f, 100.0f);
// 		txtBox->entity->GetComponent<SFENG::Transform>().size = Vec2f(150.0f, 25.0f);
// 		SFENG::UI::TextEnterHandler *txtHandler = &txtBox->entity->GetComponent<SFENG::UI::TextEnterHandler>();
// 		txtHandler->SetBoxColor(sf::Color::Blue);
// 		txtHandler->SetCharacterSize(16);
// 		txtHandler->SetMaxNumOfChars(60);
// 		txtHandler->SetTextColor(sf::Color::Black);
// 	}
// }

// void CustomScene::Main()
// {
// 	AddBox("Ground", Vec2f(400.0f, 600.0f), Vec2f(1200.f, 50.0f), b2BodyType::b2_staticBody);
// 	std::mt19937 random(time(0));
// 	std::uniform_real_distribution<float> xPos(100.0f, 500.0f);
// 	std::uniform_real_distribution<float> yPos(100.0f, 300.0f);
// 	for (int i = 0; i < 100; i++)
// 	{
// 		AddBox("Box" + std::to_string(i), Vec2f(xPos(random), yPos(random)), {10.0f, 10.0f}, b2BodyType::b2_dynamicBody);
// 		AddCircle("Circle" + std::to_string(i), Vec2f(xPos(random), yPos(random)), 10.0f, b2BodyType::b2_dynamicBody);
// 	}
// }

// void CustomScene::AddSelectBox()
// {
// 	SFENG::Entity *selectBox = this->m_LCManager.CreateEntity("SelectBox");
// 	SFENG::Highlightable *boxShape = &selectBox->AddComponent<SFENG::Highlightable>();
// 	boxShape->ListenToKeys(true);
// 	OnClick *clk = &selectBox->AddComponent<OnClick>();
// 	SFENG::Transform &trans = selectBox->GetComponent<SFENG::Transform>();
// 	trans.position = Vec2f(350.0f, 200.0f);
// 	trans.size = Vec2f(150.0f, 150.0f);
// }

// void CustomScene::AddSprite()
// {
// 	SFENG::ResourceManager::AddTexture("SampleSprite.png", "Sample");
// 	SFENG::Entity *en = this->m_LCManager.CreateEntity("Entity");
// 	SFENG::Transform &transform = en->GetComponent<SFENG::Transform>();
// 	transform.position = {200.0f, 200.0f};
// 	transform.size = {32.0f, 32.0f};
// 	SFENG::SpriteRenderer &sr = en->AddComponent<SFENG::SpriteRenderer>();
// 	SFENG::Animator &animator = en->AddComponent<SFENG::Animator>();
// 	sr.AttachTexture("Sample");
// 	SFENG::Animation *IDLEAnimation = animator.AddAnimation("IDLE");
// 	sf::Time delay = sf::seconds(0.15f);
// 	sf::IntRect rect = {0, 0, 32, 32};
// 	IDLEAnimation->AddFrame(rect, delay);
// 	rect.left = 32;
// 	IDLEAnimation->AddFrame(rect, delay);
// 	rect.left = 64;
// 	IDLEAnimation->AddFrame(rect, delay);
// 	rect.left = 96;
// 	IDLEAnimation->AddFrame(rect, delay);
// 	rect.left = 64;
// 	IDLEAnimation->AddFrame(rect, delay);
// 	rect.left = 32;
// 	IDLEAnimation->AddFrame(rect, delay);
// 	animator.SetActiveAnimation("IDLE");
// 	IDLEAnimation->Loop(true);
// }

// void CustomScene::AddCanvas()
// {
// 	SFENG::UI::Canvas canvas("Canvas1", m_LCManager);
// 	std::string textBoxName = canvas.AddElement("Test TextBox", SFENG::UI::UIElementType::TextBox);
// 	SFENG::UI::Textbox *txtBox = dynamic_cast<SFENG::UI::Textbox *>(canvas.GetElement(textBoxName));
// 	txtBox->entity->GetComponent<SFENG::Transform>().position = Vec2f(300.0f, 400.0f);
// 	SFENG::UI::TextEnterHandler *txtHandler = &txtBox->entity->GetComponent<SFENG::UI::TextEnterHandler>();
// 	txtHandler->SetBoxColor(sf::Color::Red);
// 	txtHandler->SetCharacterSize(25);
// 	txtHandler->SetMaxNumOfChars(60);
// 	txtHandler->SetTextColor(sf::Color::Green);
// }

// void CustomScene::AddBox(const std::string &name, const Vec2f &position, const Vec2f &size, b2BodyType type)
// {
// 	SFENG::Entity *newEntity = m_LCManager.CreateEntity(name);
// 	m_Entities[name] = newEntity;
// 	SFENG::Transform &trans = newEntity->GetComponent<SFENG::Transform>();
// 	trans.size = size;
// 	trans.position = position;
// 	SFENG::RigidBody2D &rb = newEntity->AddComponent<SFENG::RigidBody2D>();
// 	SFENG::BoxCollider &boxCol = newEntity->AddComponent<SFENG::BoxCollider>();
// 	BoxShape &shape = newEntity->AddComponent<BoxShape>();
// 	rb.SetBodyType(type);
// }

// void CustomScene::AddCircle(const std::string &name, const Vec2f &position, float radius, b2BodyType type)
// {
// 	SFENG::Entity *newEntity = m_LCManager.CreateEntity(name);
// 	m_Entities[name] = newEntity;
// 	SFENG::Transform &trans = newEntity->GetComponent<SFENG::Transform>();
// 	trans.size = {radius, radius};
// 	trans.position = position;
// 	SFENG::RigidBody2D &rb = newEntity->AddComponent<SFENG::RigidBody2D>();
// 	SFENG::CircleCollider &boxCol = newEntity->AddComponent<SFENG::CircleCollider>();
// 	CircleShape &shape = newEntity->AddComponent<CircleShape>();
// 	rb.SetBodyType(type);
// }

// int main()
// {
// 	CustomGame game;
// 	game.Run();
// 	return 0;
// }