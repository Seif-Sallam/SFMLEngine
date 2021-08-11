#pragma once
#include "PCH.h"

namespace SFENG {
	class Engine;
	
	
	class State
	{
	public:
		State(Engine& game)
			: m_Game(game)
		{}

		virtual ~State() = default;

		virtual void HandleEvent(sf::Event) {}

		virtual void HandleInput() = 0;
		virtual void HandleInputSlow() {};
		virtual void Update(sf::Time) {}
		virtual void FixedUpdate(sf::Time) {}
		virtual void Draw(sf::RenderWindow& target) = 0;
	protected:
		Engine& m_Game;
	};
}