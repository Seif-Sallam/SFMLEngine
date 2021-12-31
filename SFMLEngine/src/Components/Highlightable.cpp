#include "../../headers/Components/Highlightable.h"
#include "../../headers/Components/Transform.h"
#include "../../headers/Entity.h"

namespace SFENG
{

	Highlightable::Highlightable()
		: m_Trans(nullptr), m_ListenToKeys(false)
	{
	}

	inline bool Highlightable::Init()
	{
		m_Trans = &entity->GetComponent<Transform>();
		return Component::Init();
	}

	bool Highlightable::IsHighlighted()
	{
		sf::FloatRect rect = sf::FloatRect(m_Trans->position - m_Trans->size / 2.0f, m_Trans->size);
		return Mouse::InBox(rect);
	}

	void Highlightable::ListenToKeys(bool value)
	{
		m_ListenToKeys = true;
	}

	sf::Mouse::Button Highlightable::KeyPressed()
	{
		if (m_ListenToKeys)
		{
			for (int i = 0; i < Mouse::m_Buttons.size(); i++)
			{
				if (Mouse::m_Buttons[i] == true)
					return static_cast<sf::Mouse::Button>(i);
			}
		}
		return sf::Mouse::ButtonCount;
	}

}