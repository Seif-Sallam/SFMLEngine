#pragma once
#include "SFML/Graphics.hpp"
#include <array>
#include "Vec2.h"
namespace SFENG {
	class Mouse 
	{
		friend class Engine;
		friend class Highlightable;
	public:
		static Vec2f GetMousePosition();
		static bool InBox(const sf::FloatRect& rect);
		static bool MouseButtonPressed(sf::Mouse::Button button);
	private:
		static void Update(sf::Event& event);
		Mouse() = default;
		static std::array<bool, sf::Mouse::ButtonCount> m_Buttons;
	};
}