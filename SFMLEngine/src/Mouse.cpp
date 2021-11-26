#include "Mouse.h"
#include "Engine.h"

std::array<bool, sf::Mouse::ButtonCount> SFENG::Mouse::m_Buttons;

inline Vec2f SFENG::Mouse::GetMousePosition()
{
	sf::RenderWindow& window = SFENG::Engine::GetWindow();
	return window.mapPixelToCoords(sf::Mouse::getPosition(window));
}

bool SFENG::Mouse::InBox(const sf::FloatRect& rect)
{
	Vec2f pos = Mouse::GetMousePosition();
	sf::FloatRect mouseRect = sf::FloatRect(pos.x, pos.y, 3.f, 3.f);
	return mouseRect.intersects(rect);
}

bool SFENG::Mouse::MouseButtonPressed(sf::Mouse::Button button)
{
	return m_Buttons[button];
}

void SFENG::Mouse::Update(sf::Event& event)
{
	switch (event.type)
	{
	case sf::Event::MouseButtonPressed:
		m_Buttons[event.mouseButton.button] = true;
		break;
	case sf::Event::MouseButtonReleased:
		m_Buttons[event.mouseButton.button] = false;
		break;
	default:
		break;
	}
}