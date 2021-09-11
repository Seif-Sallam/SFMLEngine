#include "../../headers/Components/Highlightable.h"
#include "../../headers/Components/Transform.h"
#include "../../headers/Entity.h"

SFENG::Highlightable::Highlightable()
	: m_Trans(nullptr), m_ListenToKeys(false)
{
}

inline bool SFENG::Highlightable::Init()
{
	m_Trans = &entity->GetCopmonent<Transform>();
	return SFENG::Component::Init();
}

bool SFENG::Highlightable::IsHighlighted()
{
	sf::FloatRect rect = sf::FloatRect(m_Trans->position - m_Trans->size / 2.0f, m_Trans->size);
	return SFENG::Mouse::InBox(rect);
}

void SFENG::Highlightable::ListenToKeys(bool value)
{
	m_ListenToKeys = true;
}

sf::Mouse::Button SFENG::Highlightable::KeyPressed()
{
	if (m_ListenToKeys) 
	{
		for (int i = 0; i < SFENG::Mouse::m_Buttons.size(); i++)
		{
			if (SFENG::Mouse::m_Buttons[i] == true)
				return static_cast<sf::Mouse::Button>(i);
		}
	}
	return sf::Mouse::ButtonCount;
}
