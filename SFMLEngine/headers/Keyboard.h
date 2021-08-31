#pragma once
#include "SFML/Graphics.hpp"
#include <array>
#include <vector>
namespace SFENG {
	class Keyboard {
	public:
		Keyboard() = delete;
		static void Update(sf::Event& event);
		static const bool IsKeyPressed(const sf::Keyboard::Key& key);
	private:
		static std::array<bool, sf::Keyboard::KeyCount> m_Keys;
	};
}
