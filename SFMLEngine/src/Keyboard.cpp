#include "../headers/Keyboard.h"

SFENG::Keyboard::Keyboard()
{
	ResetKeys();
}

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

const bool SFENG::Keyboard::IsKeyPressed(const sf::Keyboard::Key& key) const
{
	return m_Keys[key];
}

void SFENG::Keyboard::ResetKeys()
{
	std::fill(m_Keys.begin(), m_Keys.end(), false);
}
