#include "UI/Canvas.h"
#include "UI/Textbox.h"
#include "Components/Transform.h"
#include "Components/SpriteRenderer.h"
#include "LifeCycleManager.h"
#include "UI/UIElement.h"
#include "Entity.h"

SFENG::UI::Canvas::Canvas(const std::string& name, LifeCycleManager& LCM)
	: m_LCM(LCM)
{
	entity = m_LCM.CreateEntity(name);
}

std::string SFENG::UI::Canvas::AddElement(const std::string& name, UIElementType type)
{
	UIElement* element = nullptr;
	std::string newName = GetNewName(name);
	switch (type)
	{
	case SFENG::UI::UIElementType::Button:
		break;
	case SFENG::UI::UIElementType::TextBox:
		element = new Textbox(m_LCM.CreateEntity(newName), this);
		break;
	case SFENG::UI::UIElementType::SlideBar:
		break;
	case SFENG::UI::UIElementType::Label:
		break;
	case SFENG::UI::UIElementType::Image:
		break;
	default:
		break;
	}
	AddElementPriv(newName, element);
	return newName;
}

SFENG::UI::UIElement* SFENG::UI::Canvas::GetElement(const std::string& name)
{
	if(m_Elements.find(name) == m_Elements.end())
		return nullptr;
	return m_Elements[name];
}

SFENG::UI::Canvas::~Canvas()
{
}

void SFENG::UI::Canvas::AddElementPriv(const std::string& name, UIElement*& element)
{
	m_ElementsNums.insert({ name, 0 });
	m_Elements.insert({ name, element });
}

std::string SFENG::UI::Canvas::GetNewName(const std::string& name)
{
	if (m_ElementsNums.find(name) == m_ElementsNums.end())
	{
		return name;
	}
	else
	{
		int32_t& num = m_ElementsNums[name];
		num++;
		std::string newName = name + std::to_string(num);
		return newName;
	}
	return std::string();
}
