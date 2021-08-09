#pragma once
#include "headers/Engine.h"

class CustomState : public SFENG::State
{
public:
	CustomState(SFENG::Engine& en) 
		: State(en)
	{
		sf::RectangleShape* shape = new sf::RectangleShape;
		sf::CircleShape* shape2 = new sf::CircleShape(5.0f);
		shape2->setFillColor(sf::Color::Blue);
		shape->setSize(Vec2f(10.0f, 10.0f));
		//shape->setFillColor(sf::Color::Blue);
		shape->setTexture(&SFENG::ResourceManager::Get().GetDefaultTexture());
		particleSystem = new SFENG::ParticleSystem(shape, Vec2f(400.0f, 500.0f), Vec2f(0, -1), 150000);
		particleSystem2 = new SFENG::ParticleSystem(shape2, Vec2f(700.0f, 300.0f), Vec2f(0, -1), 150000);
		particleSystem3 = new SFENG::ParticleSystem(shape2, Vec2f(200.0f, 300.0f), Vec2f(0, -1), 150000);
	}

	~CustomState()
	{
		delete particleSystem;
	}

	void HandleEvent(sf::Event) override {
		
	}

	void HandleInput() override {
		if (SFENG::Keyboard::IsKeyPressed(sf::Keyboard::Key::A))
			m_Game.view.move(-10.0f, 0.0f);
		if (SFENG::Keyboard::IsKeyPressed(sf::Keyboard::Key::D))
			m_Game.view.move(10.0f, 0.0f);
		if (SFENG::Keyboard::IsKeyPressed(sf::Keyboard::Key::W))
			m_Game.view.move(0.0f, -10.0f);
		if (SFENG::Keyboard::IsKeyPressed(sf::Keyboard::Key::S))
			m_Game.view.move(0.0f, 10.0f);
		if (SFENG::Keyboard::IsKeyPressed(sf::Keyboard::Key::B))
			particleSystem->Stop();
		if (SFENG::Keyboard::IsKeyPressed(sf::Keyboard::Key::Escape))
			m_Game.ExitGame();
	}
	void Update(sf::Time t) override {
		particleSystem->Update(t);
		particleSystem2->Update(t);
		particleSystem3->Update(t);
	}
	void FixedUpdate(sf::Time) override {
	}
	void Draw(sf::RenderWindow& target) override {
		sf::RectangleShape shape;
		shape.setFillColor(sf::Color::Black);
		shape.setPosition(Vec2f(200, 300));
		shape.setSize(Vec2f(150, 150));
		target.draw(shape);
		particleSystem->Draw(target);
		particleSystem2->Draw(target);
		particleSystem3->Draw(target);
	}

private:
	SFENG::ParticleSystem* particleSystem;
	SFENG::ParticleSystem* particleSystem2;
	SFENG::ParticleSystem* particleSystem3;
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