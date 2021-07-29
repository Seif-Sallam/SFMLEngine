#pragma once
#include "PCH.h"

namespace SFENG {
	class Keyboard {
	public:
		static void Update(sf::Event& event);
		static const bool IsKeyPressed(const sf::Keyboard::Key& key);
	private:
		static std::array<bool, sf::Keyboard::KeyCount> m_Keys;
	};
}
