#pragma once
#include "PCH.h"

namespace SFENG {
	class Keyboard {
	public:
		Keyboard();
		void Update(sf::Event& event);
		const bool IsKeyPressed(const sf::Keyboard::Key& key) const;
	private:
		void ResetKeys();
		std::array<bool, sf::Keyboard::KeyCount> m_Keys;
	};
}
