#pragma once
#include "PCH.h"

namespace SFENG {
	class Engine;

	class State
	{
	public:
		State(Engine& engine)
			: m_Engine(engine)
		{}

		virtual ~State() = default;

		virtual void HandleEvent(sf::Event) {}

		virtual void HandleInput() = 0;
		virtual void HandleInputSlow() {};
		virtual void Update(sf::Time) {}
		virtual void FixedUpdate(sf::Time) {}
		virtual void Draw(sf::RenderWindow& target) = 0;
	protected:
		Engine& m_Engine;
	};
}