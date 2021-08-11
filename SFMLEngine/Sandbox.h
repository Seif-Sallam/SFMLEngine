#pragma once
#include "headers/Engine.h"

class CustomState : public SFENG::State
{
public:
	CustomState(SFENG::Engine& en) 
		: State(en)
	{
		sf::CircleShape* shape2 = new sf::CircleShape(5.0f);
		shape2->setFillColor(sf::Color::Green);

		particleSystem = new SFENG::UFParticleSystem(shape2, Vec2f(400.0f, 500.0f), Vec2f(0, -1), 150000);
		particleSystem->SetIntensity(1);
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
			particleSystem->SetIntensity(++intensity);
		if (SFENG::Keyboard::IsKeyPressed(sf::Keyboard::Key::U))
			particleSystem->SetIntensity(--intensity);
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
		if (SFENG::Keyboard::IsKeyPressed(sf::Keyboard::Key::B))
			particleSystem->Stop();

		if (SFENG::Keyboard::IsKeyPressed(sf::Keyboard::Key::Escape))
			m_Game.ExitGame();
	}
	void Update(sf::Time t) override {
		particleSystem->Update(t);
	}
	void FixedUpdate(sf::Time) override {
		m_Game.GetWindow().setTitle(std::to_string(intensity));
	}
	void Draw(sf::RenderWindow& target) override {
		particleSystem->Draw(target);
	}

private:
	SFENG::UFParticleSystem* particleSystem;
	sf::Clock clk;
	int intensity = 1;
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