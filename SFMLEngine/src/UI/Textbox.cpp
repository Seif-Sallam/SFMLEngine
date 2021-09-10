#include "../../headers/UI/Textbox.h"
#include "../../headers/UI/Canvas.h"
#include "../../headers/Entity.h"
#include "../../headers/ResourceManager.h"


SFENG::UI::Textbox::Textbox(Entity* entity, Canvas* parentCanvas)
	: UIElement(parentCanvas, entity)
{
	Initialize();
}

void SFENG::UI::Textbox::Initialize()
{
	Transform& boxTrans = m_Entity->GetCopmonent<Transform>();
	Entity*& canvasEntity = m_Canvas->operator SFENG::Entity * &();
	Transform& canvasTrans = canvasEntity->GetCopmonent<Transform>();
	boxTrans.position = canvasTrans.position;
	boxTrans.size = {50.0f, 20.0f};
	m_WriteTextComp = &m_Entity->AddComponent<WriteText>();
	m_WriteTextComp->SetFont("Default");
}

SFENG::UI::Textbox::WriteText::WriteText()
	: m_Transform(nullptr), m_MinSize(Vec2f(50.0f, 20.0f)), m_MaxCharacters(30)
{
}

void SFENG::UI::Textbox::WriteText::SetFont(const std::string& fontName)
{
	sf::Font& font = SFENG::ResourceManager::GetFont(fontName);
	text.setFont(font);
}

bool SFENG::UI::Textbox::WriteText::Init()
{
	m_Shape.setSize(m_MinSize);
	m_Shape.setOrigin(m_MinSize / 2.0f);
	m_Shape.setFillColor(sf::Color::Transparent);
	m_Shape.setOutlineColor(sf::Color::Black);
	m_Shape.setOutlineThickness(1.5f);
	m_Transform = &this->entity->GetCopmonent<Transform>();
	CenterText();
	m_Shape.setPosition(m_Transform->position.x - 2.f, m_Transform->position.y - 2.f);
	text.setCharacterSize(24);
	return Component::Init();
}

inline void SFENG::UI::Textbox::WriteText::HandleEvents(sf::Event& event)
{
	if(m_ActualText.size() - 1 < m_MaxCharacters)
		if (event.type == sf::Event::TextEntered)
		{
			if (ValidText(event.text.unicode))
			{
				if (event.text.unicode == '\b' && m_ActualText.size() > 0)
						m_ActualText.pop_back();
				else
					m_ActualText.push_back(event.text.unicode);
				text.setString(m_ActualText);
				CenterText();
				auto rect = text.getLocalBounds();
				if (rect.width + 2.f > m_MinSize.x) 
				{
					Vec2f newSize(rect.width + 2.f, 20.0f);
					m_Shape.setSize(newSize);
				}
				else
				{
					m_Shape.setSize(m_MinSize);
				}
			}
		}
	return Component::HandleEvents(event);
}

void SFENG::UI::Textbox::WriteText::Update(const sf::Time& elapsedTime)
{
	CenterText();
	m_Shape.setPosition(m_Transform->position.x - 2.f, m_Transform->position.y - 2.f);
}

void SFENG::UI::Textbox::WriteText::CenterText()
{
	Vec2f pos = m_Transform->position;
	auto rect = text.getLocalBounds();
	pos.x += rect.width / 2.0f;
	text.setPosition(pos);
}

bool SFENG::UI::Textbox::WriteText::ValidText(uint32_t unicode)
{
	if (unicode == '\b' || unicode == ' '
		|| unicode >= '0' && unicode <= '9'
		|| unicode >= 'A' && unicode <= 'Z'
		|| unicode >= 'a' && unicode <= 'z')
		return true;
	return false;
}
