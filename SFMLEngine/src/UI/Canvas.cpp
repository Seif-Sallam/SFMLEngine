#include "../../headers/UI/Canvas.h"
#include "../../headers/Components/Transform.h"
#include "../../headers/Components/SpriteRenderer.h"

SFENG::UI::Canvas::Canvas(LifeCycleManager& LCM)
	: m_LCM(LCM), m_Entity(nullptr)
{
}

std::string SFENG::UI::Canvas::AddElement(const std::string& name, UIElement* element)
{
	if (m_ElementsNums.find(name) == m_ElementsNums.end())
	{
		m_Elements.insert({ name, element });
		m_ElementsNums.insert({ name, 0 });
		return name;
	}
	else
	{
		int32_t& num = m_ElementsNums[name];
		num++;
		std::string newName = name + std::to_string(num);
		m_ElementsNums.insert({ newName, 0 });
		m_Elements.insert({ newName, element });
		return newName;
	}
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
