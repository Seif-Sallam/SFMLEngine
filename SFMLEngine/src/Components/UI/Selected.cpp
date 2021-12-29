#include "../../../headers/Components/UI/Selected.h"
#include "../../../headers/Components/Transform.h"
#include "../../../headers/Components/Highlightable.h"
#include "../../../headers/Entity.h"

bool SFENG::UI::Selected::Init()
{
	m_Highlightable = &entity->GetComponent<Highlightable>();
	return Component::Init();
}

void SFENG::UI::Selected::HandleEvents(sf::Event &event)
{
	if (m_Highlightable != nullptr)
	{
		auto button = m_Highlightable->KeyPressed();
		if (m_Highlightable->IsHighlighted() && button == sf::Mouse::Button::Left)
			m_Pressed = true;
		else if (!m_Highlightable->IsHighlighted() && button == sf::Mouse::Button::Left)
			m_Pressed = false;
	}
	return Component::HandleEvents(event);
}
