#pragma once
/*
	Singlton class to maintain the behviour of the Keyboard and
	keeps track of the pressed and released buttons of the keyboard.
*/

#include "SFML/Graphics.hpp"
#include <array>
#include <vector>

namespace SFENG {
	// The class here serves the same purpose of a namespace 
	// but with data members hiding.
	class Keyboard {
		friend class Engine;
	public:
		Keyboard() = delete; 
		static const bool IsKeyPressed(const sf::Keyboard::Key& key);
	private:
		static void Update(sf::Event& event);
		static std::array<bool, sf::Keyboard::KeyCount> m_Keys;
	};
}
