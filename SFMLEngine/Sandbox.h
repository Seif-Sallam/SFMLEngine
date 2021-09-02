//#pragma once
//
//#include "headers/Engine.h"
//
//class CustomState : public SFENG::State
//{
//public:
//	CustomState(SFENG::Engine& en)
//		: State(en)
//	{
//		sf::CircleShape* shape2 = new sf::CircleShape(10.0f);
//		shape2->setFillColor(sf::Color::Transparent);
//		//shape2->setOutlineColor(sf::Color::Black);
//		//shape2->setOutlineThickness(2);
//		particleSystem = new SFENG::ParticleFountain(shape2, Vec2f(200.0f, 200.0f), Vec2f(0, -1), 150000);
//		particleSystem->SetIntensity(1);
//		/*for (int i = 0; i < 5; i++)
//		{
//			for (int j = 0; j < 15; j++) {
//				particleSystems.push_back(new SFENG::ParticleFountain(shape2, Vec2f(j * 50 + 50.0f, 100 * i + 100.0f), Vec2f(0, -1), 150000));
//				particleSystems.back()->SetAngle(90.0f);
//				particleSystems.back()->SetIntensity(7);
//			}
//		}*/
//		angleText.setFont(SFENG::ResourceManager::Get().GetDefaultFont());
//		intensityText.setFont(SFENG::ResourceManager::Get().GetDefaultFont());
//		widthText.setFont(SFENG::ResourceManager::Get().GetDefaultFont());
//		angleText.setPosition(Vec2f(10.0f, 200.0f));
//		intensityText.setPosition(Vec2f(10.0f, 250.0f));
//		widthText.setPosition(Vec2f(10.0f, 300.0f));
//		angleText.setCharacterSize(15);
//		intensityText.setCharacterSize(15);
//		widthText.setCharacterSize(15);
//		SFENG::ResourceManager::Get().AddTexture("rsc/Textures/Sheet.png", "Sheet");
//		t = new SFENG::Tilemap(Vec2i(4, 4), Vec2f(0.0f, 0.0f), Vec2f(32.0f, 32.0f), "Sheet", m_Engine.GetWindow());
//		t->ReadMap("file2.txt");
//
//		const b2Vec2 gravity(1.0f, 20.f);
//		m_PhysWorld = new b2World(gravity);
//
//		b2BodyDef groundBodyDef;
//		groundBodyDef.position.Set(300.0f, 500.0f);
//		b2Body* groundBody = m_PhysWorld->CreateBody(&groundBodyDef);
//		b2PolygonShape groundBoxShape;
//		groundBoxShape.SetAsBox(500.0f, 10.0f);
//		b2Fixture* f = groundBody->CreateFixture(&groundBoxShape, 0.0f);
//
//		std::mt19937 randomGen(time(0));
//		std::uniform_real_distribution<float> xPos(75.0f, 150.f);
//		std::uniform_real_distribution<float> yPos(0, 300.0f);
//
//		for (int i = 0; i < 5; i++) {
//			CustomBox box;
//			float x = xPos(randomGen);
//			float y = yPos(randomGen);
//			if (y < 50.f)
//				box.Init(m_PhysWorld, Vec2f(x, y), Vec2f(20.0f, 20.0f), sf::Color::Blue);
//			else
//				box.Init(m_PhysWorld, Vec2f(x, y), Vec2f(20.0f, 20.0f), sf::Color::Red);
//			boxes.push_back(box);
//		}
//	}
//
//	~CustomState()
//	{
//		for (int i = 0; i < particleSystems.size(); i++)
//			delete particleSystems[i];
//		particleSystems.clear();
//		delete particleSystem;
//	}
//
//	void HandleEvent(sf::Event) override {
//	}
//	void HandleInputSlow() override
//	{
//		if (SFENG::Keyboard::IsKeyPressed(sf::Keyboard::Key::I))
//		{
//			intensity = (intensity + 1) % 11;
//			particleSystem->SetIntensity(intensity);
//		}
//		if (SFENG::Keyboard::IsKeyPressed(sf::Keyboard::Key::U))
//		{
//			intensity = (intensity - 1) % 11;
//			if (intensity <= 0) intensity = 1;
//			particleSystem->SetIntensity(intensity);
//		}
//		if (SFENG::Keyboard::IsKeyPressed(sf::Keyboard::Key::K)) {
//			angle = float((int)(angle - 1) % 360);
//			if (angle < 0) angle = 0;
//			particleSystem->SetAngle(angle);
//		}
//		if (SFENG::Keyboard::IsKeyPressed(sf::Keyboard::Key::L)) {
//			angle = (int)(angle + 1) % 360;
//			particleSystem->SetAngle(angle);
//		}
//		if (SFENG::Keyboard::IsKeyPressed(sf::Keyboard::Key::N) && width > 1) {
//			particleSystem->SetWidth(--width);
//		}
//		if (SFENG::Keyboard::IsKeyPressed(sf::Keyboard::Key::M))
//			particleSystem->SetWidth(++width);
//	}
//
//	void HandleInput() override {
//		if (SFENG::Keyboard::IsKeyPressed(sf::Keyboard::Key::A))
//			particleSystem->Move({ -10.0f, 0.0f });
//		if (SFENG::Keyboard::IsKeyPressed(sf::Keyboard::Key::D))
//			particleSystem->Move({ 10.0f, 0.0f });
//		if (SFENG::Keyboard::IsKeyPressed(sf::Keyboard::Key::W))
//			particleSystem->Move({ 0.0f, -10.0f });
//		if (SFENG::Keyboard::IsKeyPressed(sf::Keyboard::Key::S))
//			particleSystem->Move({ 0.0f, 10.0f });
//		if (SFENG::Keyboard::IsKeyPressed(sf::Keyboard::Key::Left))
//			m_Engine.engineView.move(-10.0f, 0.0f);
//		if (SFENG::Keyboard::IsKeyPressed(sf::Keyboard::Key::Right))
//			m_Engine.engineView.move(10.0f, 0.0f);
//		if (SFENG::Keyboard::IsKeyPressed(sf::Keyboard::Key::Up))
//			m_Engine.engineView.move(0.0f, -10.0f);
//		if (SFENG::Keyboard::IsKeyPressed(sf::Keyboard::Key::Down))
//			m_Engine.engineView.move(0.0f, 10.0f);
//
//		if (SFENG::Keyboard::IsKeyPressed(sf::Keyboard::Key::Escape))
//			m_Engine.ExitGame();
//	}
//	void Update(sf::Time t) override {
//
//		particleSystem->Update(t);
//		for (auto& i : particleSystems)
//			i->Update(t);
//		intensityText.setString("Intensity Press U AND I: " + std::to_string(intensity));
//		widthText.setString("Width Press N AND M: " + std::to_string(width));
//		angleText.setString("Angle Press K AND L: " + std::to_string((int)angle));
//	}
//	void FixedUpdate(sf::Time) override {
//		m_PhysWorld->Step(1.0f / 60.0f, 6, 2);
//		for (auto& b : boxes) {
//			b.Update();
//		}
//	}
//	void Draw(sf::RenderWindow& window) override {
//		particleSystem->Draw(window);
//		for (auto& i : particleSystems)
//			i->Draw(window);
//		window.draw(intensityText);
//		window.draw(angleText);
//		window.draw(widthText);
//		t->Darw();
//
//		for (auto& b : boxes)
//			b.Draw(window);
//	}
//
//private:
//	SFENG::ParticleFountain* particleSystem;
//	std::vector<SFENG::ParticleFountain*>  particleSystems;
//	sf::Clock clk;
//	int intensity = 1;
//	int width = 5;
//	float angle = 10.f;
//	sf::Text angleText;
//	sf::Text widthText;
//	sf::Text intensityText;
//	SFENG::Tilemap* t;
//	b2World* m_PhysWorld;
//	class CustomBox {
//	public:
//		CustomBox() {}
//		~CustomBox() {}
//		void Init(b2World* world, const Vec2f& position, const Vec2f& dim, const sf::Color& color)
//		{
//			this->world = world;
//			this->dim   = dim;
//
//			sfShape.setOrigin(dim.x / 2.0f, dim.y / 2.0f);
//			sfShape.setPosition(position.x, position.y);
//			sfShape.setSize(sf::Vector2f(dim.x, dim.y));
//			sfShape.setFillColor(color);
//
//			//Create the body definition;
//			b2BodyDef bodyDef;
//			bodyDef.position.Set(position.x, position.y);
//			bodyDef.type = b2_dynamicBody;
//
//			//Create the body itself
//			body = world->CreateBody(&bodyDef);
//			b2PolygonShape shape;
//			shape.SetAsBox(dim.x / 2.0f, dim.y / 2.0f);
//
//			b2FixtureDef fixtureDef;
//			fixtureDef.density = 1.0f;
//			fixtureDef.friction = 0.3f;
//			fixtureDef.shape = &shape;
//
//			fixture = body->CreateFixture(&fixtureDef);
//		}
//
//		void Update()
//		{
//			float rot = body->GetAngle() * 180.0f / M_PI;
//			auto pos  = body->GetPosition();
//			sfShape.setPosition(pos.x, pos.y);
//			sfShape.setRotation(rot);
//		}
//		void Draw(sf::RenderWindow& window)
//		{
//			window.draw(sfShape);
//		}
//		sf::RectangleShape sfShape;
//		b2Body* body;
//		b2World* world;
//		b2Fixture* fixture;
//		Vec2f dim;
//	};
//
//	std::vector<CustomBox> boxes;
//};
//
//class Sandbox : public SFENG::Engine
//{
//public:
//	Sandbox() {
//		std::unique_ptr<CustomState> state = std::make_unique<CustomState>(*this);
//		PushStartingScene(std::move(state));
//	}
//	~Sandbox() {}
//
//	void HandleScenes()
//	{
//		float passedTime = clk.getElapsedTime().asSeconds();
//	}
//private:
//	sf::Clock clk;
//};

