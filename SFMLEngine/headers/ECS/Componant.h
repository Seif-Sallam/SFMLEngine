#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
namespace SFENG {
	class Entity;

	class Component {
	public:
		Component() = default;
		virtual ~Component()
		{
#ifdef  _DEBUG
			std::cout << "In Componant Destructor\n";
#endif //  _DEBUG
		}
		Entity* entity = nullptr;

		inline virtual bool Init() { m_IsValid = true; return true; };
		inline virtual void Draw(sf::RenderWindow* window) {  }
		inline virtual void Update(float deltaTime) {}
		inline virtual void HandleEvents(sf::Event* event) {}
		inline virtual void Print() { std::cout << "Raw Component\n"; }
		bool IsValid() { return m_IsValid; };

	protected:
		bool m_IsValid = false;
	};
}