#pragma once
#include "PCH.h"

namespace SFENG {
	class Keyboard {
	public:
		Keyboard();
		static void Update(sf::Event& event);
		static const bool IsKeyPressed(const sf::Keyboard::Key& key);
	private:
		void ResetKeys();
		static std::array<bool, sf::Keyboard::KeyCount> m_Keys;
	};
}
