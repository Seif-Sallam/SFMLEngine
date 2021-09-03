#include "../headers/Keyboard.h"
// Static data members declaration
std::array<bool, sf::Keyboard::KeyCount> SFENG::Keyboard::m_Keys;

void SFENG::Keyboard::Update(sf::Event& event)
{
	switch (event.type)
	{
	case sf::Event::KeyPressed:
		m_Keys[event.key.code] = true;
		break;
	case sf::Event::KeyReleased:
		m_Keys[event.key.code] = false;
		break;
	default:
		break;
	}
}

const bool SFENG::Keyboard::IsKeyPressed(const sf::Keyboard::Key& key)
{
	return m_Keys[key];
}