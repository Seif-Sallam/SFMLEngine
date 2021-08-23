#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>

class Entity;

namespace SFENG {
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
		inline bool IsValid() { return m_IsValid; }

		Entity* entity = nullptr;
	protected:
		bool m_IsValid = false;
	};

}