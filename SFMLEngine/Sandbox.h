#pragma once
#include "headers/Engine.h"

class CustomState : public SFENG::State
{
public:
	CustomState(SFENG::Engine& en) 
		: State(en)
	{
	}
	void HandleEvent(sf::Event) {
		
	}

	void HandleInput() {
		if (SFENG::Keyboard::IsKeyPressed(sf::Keyboard::Key::A))
			m_Game.view.move(-10.0f, 0.0f);
		if (SFENG::Keyboard::IsKeyPressed(sf::Keyboard::Key::D))
			m_Game.view.move(10.0f, 0.0f);
		if (SFENG::Keyboard::IsKeyPressed(sf::Keyboard::Key::W))
			m_Game.view.move(0.0f, -10.0f);
		if (SFENG::Keyboard::IsKeyPressed(sf::Keyboard::Key::S))
			m_Game.view.move(0.0f, 10.0f);
		if (SFENG::Keyboard::IsKeyPressed(sf::Keyboard::Key::Escape))
			m_Game.ExitGame();
	}
	void Update(sf::Time) {
	
	}
	void FixedUpdate(sf::Time) {
	}
	void Draw(sf::RenderTarget& target) {
		sf::RectangleShape shape;
		shape.setFillColor(sf::Color::Black);
		shape.setPosition(Vec2f(200, 300));
		shape.setSize(Vec2f(150, 150));
		target.draw(shape);
	}

private:

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