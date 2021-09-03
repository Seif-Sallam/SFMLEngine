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

		virtual bool Init() { m_IsValid = true; return true; }
		virtual void Draw(sf::RenderWindow& window) {}
		virtual void Update(const sf::Time& elapsedTime) {}
		virtual void FixedUpdate(const sf::Time& elapsedTime) {}
		virtual void HandleEvents(sf::Event& event) {}
		virtual void Print() { std::cout << "Raw Copmonent\n"; }
		bool IsValid() { return m_IsValid; }
		void MakeUnValid() { m_IsValid = true; }
		Entity* entity = nullptr;
	protected:
		bool m_IsValid = false;
	};
}