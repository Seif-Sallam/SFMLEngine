#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>

namespace SFENG {
	class Entity;
	/// Base class of the Components
	class Component {
	public:
		Component() = default;

		virtual ~Component() = default;

		inline virtual bool Init() { m_IsValid = true; return true; }
		inline virtual void Draw(sf::RenderWindow& window) {}
		inline virtual void Update(const sf::Time& elapsedTime) {}
		inline virtual void FixedUpdate(const sf::Time& elapsedTime) {}
		inline virtual void HandleEvents(sf::Event& event) {}
		inline virtual void Print() { std::cout << "Raw Copmonent\n"; }
		inline void SetRenderState(sf::RenderStates state) { m_RenderState = state; }
		bool IsValid() { return m_IsValid; }
		void MakeUnValid() { m_IsValid = true; }
		Entity* entity = nullptr;
	protected:
		bool m_IsValid = false;
		sf::RenderStates m_RenderState;
	};
}