#include "../../../headers/Components/UI/TextEnterHandler.h"
#include "../../../headers/Entity.h"
#include "../../../headers/ResourceManager.h"

SFENG::UI::TextEnterHandler::TextEnterHandler()
	: m_Transform(nullptr), m_MinSize(Vec2f(150.0f, 25.0f)), m_MaxCharacters(50)
{
}

void SFENG::UI::TextEnterHandler::SetFont(const std::string& fontName)
{
	sf::Font& font = SFENG::ResourceManager::GetFont(fontName);
	text.setFont(font);
}

bool SFENG::UI::TextEnterHandler::Init()
{
	m_Shape.setSize(m_MinSize);
	m_Shape.setOrigin(m_MinSize / 2.0f);
	m_Shape.setFillColor(sf::Color::Transparent);
	m_Shape.setOutlineColor(sf::Color::Black);
	m_Shape.setOutlineThickness(1.5f);
	m_Transform = &this->entity->GetCopmonent<Transform>();
	m_Shape.setPosition(m_Transform->position.x - 2.f, m_Transform->position.y - 2.f);
	text.setCharacterSize(15);
	text.setFillColor(sf::Color::Blue);
	return Component::Init();
}

inline void SFENG::UI::TextEnterHandler::HandleEvents(sf::Event& event)
{
	if (event.type == sf::Event::TextEntered)
	{
		if (ValidText(event.text.unicode))
		{
			AddText(event.text.unicode);
			text.setString(m_ActualText);
			CenterText();
		}
	}
	return Component::HandleEvents(event);
}

void SFENG::UI::TextEnterHandler::Update(const sf::Time& elapsedTime)
{
	if (m_Transform->position != Vec2f(m_Shape.getPosition()))
		CenterText();
}

void SFENG::UI::TextEnterHandler::AddText(uint32_t value)
{
	if (value == '\b') {
		if (m_ActualText.size() > 0) {
			m_ActualText.pop_back();
		}
	}
	else if ((int)m_ActualText.size() - 1 < m_MaxCharacters)
		m_ActualText.push_back(value);
}

void SFENG::UI::TextEnterHandler::CenterText()
{
	auto rect = text.getLocalBounds();
	text.setOrigin(text.getLocalBounds().width / 2.0f, (m_MinSize.h - 2.0f) / 2.0f);
	Vec2f pos = m_Transform->position;
	text.setPosition(pos);
	Vec2f newSize(std::max(rect.width + 20.f, m_MinSize.x), m_MinSize.h);
	m_Shape.setSize(newSize);
	m_Shape.setOrigin(newSize / 2.0f);
	m_Shape.setPosition(m_Transform->position);
}

bool SFENG::UI::TextEnterHandler::ValidText(uint32_t unicode)
{
	if (unicode == '\b' || unicode >= 32 && unicode <= 128)
		return true;
	return false;
}
