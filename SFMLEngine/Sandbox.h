#pragma once
#include "headers/Engine.h"

class CustomState : public SFENG::State
{
public:
	CustomState(SFENG::Engine& en)
		: State(en)
	{
		sf::CircleShape* shape2 = new sf::CircleShape(10.0f);
		shape2->setFillColor(sf::Color::Transparent);
		//shape2->setOutlineColor(sf::Color::Black);
		//shape2->setOutlineThickness(2);
		particleSystem = new SFENG::ParticleFountain(shape2, Vec2f(200.0f, 200.0f), Vec2f(0, -1), 150000);
		particleSystem->SetIntensity(1);
		/*for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 15; j++) {
				particleSystems.push_back(new SFENG::ParticleFountain(shape2, Vec2f(j * 50 + 50.0f, 100 * i + 100.0f), Vec2f(0, -1), 150000));
				particleSystems.back()->SetAngle(90.0f);
				particleSystems.back()->SetIntensity(7);
			}
		}*/
		angleText.setFont(SFENG::ResourceManager::Get().GetDefaultFont());
		intensityText.setFont(SFENG::ResourceManager::Get().GetDefaultFont());
		widthText.setFont(SFENG::ResourceManager::Get().GetDefaultFont());
		angleText.setPosition(Vec2f(10.0f, 200.0f));
		intensityText.setPosition(Vec2f(10.0f, 250.0f));
		widthText.setPosition(Vec2f(10.0f, 300.0f));
		angleText.setCharacterSize(15);
		intensityText.setCharacterSize(15);
		widthText.setCharacterSize(15);
		SFENG::ResourceManager::Get().AddTexture("rsc/Textures/Sheet.png", "Sheet");
		t = new SFENG::Tilemap(Vec2i(4, 4), Vec2f(0.0f, 0.0f), Vec2f(32.0f, 32.0f), "Sheet", m_Engine.GetWindow());
		t->ReadMap("file2.txt");
	}

	~CustomState()
	{
		delete particleSystem;
	}

	void HandleEvent(sf::Event) override {

	}
	void HandleInputSlow() override
	{
		if (SFENG::Keyboard::IsKeyPressed(sf::Keyboard::Key::I))
		{
			intensity = (intensity + 1) % 11;
			particleSystem->SetIntensity(intensity);
		}
		if (SFENG::Keyboard::IsKeyPressed(sf::Keyboard::Key::U))
		{
			intensity = (intensity - 1) % 11;
			if (intensity <= 0) intensity = 1;
			particleSystem->SetIntensity(intensity);
		}
		if (SFENG::Keyboard::IsKeyPressed(sf::Keyboard::Key::K)) {
			angle = (int)(angle - 1) % 360;
			if (angle < 0) angle = 0;
			particleSystem->SetAngle(angle);
		}
		if (SFENG::Keyboard::IsKeyPressed(sf::Keyboard::Key::L)) {
			angle = (int)(angle + 1) % 360;
			particleSystem->SetAngle(angle);
		}
		if (SFENG::Keyboard::IsKeyPressed(sf::Keyboard::Key::N) && width > 1) {
			particleSystem->SetWidth(--width);
		}
		if (SFENG::Keyboard::IsKeyPressed(sf::Keyboard::Key::M))
			particleSystem->SetWidth(++width);
			
			
	}

	void HandleInput() override {
		if (SFENG::Keyboard::IsKeyPressed(sf::Keyboard::Key::A))
			particleSystem->Move({ -10.0f, 0.0f });
		if (SFENG::Keyboard::IsKeyPressed(sf::Keyboard::Key::D))
			particleSystem->Move({  10.0f, 0.0f });
		if (SFENG::Keyboard::IsKeyPressed(sf::Keyboard::Key::W))
			particleSystem->Move({ 0.0f, -10.0f });
		if (SFENG::Keyboard::IsKeyPressed(sf::Keyboard::Key::S))
			particleSystem->Move({ 0.0f, 10.0f  });
		if (SFENG::Keyboard::IsKeyPressed(sf::Keyboard::Key::Left))
			m_Engine.engineView.move(-10.0f, 0.0f);
		if (SFENG::Keyboard::IsKeyPressed(sf::Keyboard::Key::Right))
			m_Engine.engineView.move(10.0f, 0.0f);
		if (SFENG::Keyboard::IsKeyPressed(sf::Keyboard::Key::Up))
			m_Engine.engineView.move(0.0f, -10.0f);
		if (SFENG::Keyboard::IsKeyPressed(sf::Keyboard::Key::Down))
			m_Engine.engineView.move(0.0f, 10.0f);


		if (SFENG::Keyboard::IsKeyPressed(sf::Keyboard::Key::Escape))
			m_Engine.ExitGame();
	}
	void Update(sf::Time t) override {
		particleSystem->Update(t);
		for (auto& i : particleSystems)
			i->Update(t);
		intensityText.setString("Intensity Press U AND I: " + std::to_string(intensity));
		widthText.setString("Width Press N AND M: " + std::to_string(width));
		angleText.setString("Angle Press K AND L: " + std::to_string((int)angle));
	}
	void FixedUpdate(sf::Time) override {
	}
	void Draw(sf::RenderWindow& target) override {
		particleSystem->Draw(target);
		for (auto& i : particleSystems)
			i->Draw(target);
		target.draw(intensityText);
		target.draw(angleText);
		target.draw(widthText);
		t->Darw();
	}

private:
	SFENG::ParticleFountain* particleSystem;
	std::vector<SFENG::ParticleFountain*>  particleSystems;
	sf::Clock clk;
	int intensity = 1;
	int width = 5;
	float angle = 10.f;
	sf::Text angleText;
	sf::Text widthText;
	sf::Text intensityText;
	SFENG::Tilemap* t;
};

class Sandbox : public SFENG::Engine
{
public:
	Sandbox() {
		std::unique_ptr<CustomState> state = std::make_unique<CustomState>(*this);
		PushStartingState(std::move(state));
	}
	~Sandbox() {}
	
	void HandleStates()
	{
		float passedTime = clk.getElapsedTime().asSeconds();
	}
private:
	sf::Clock clk;

};