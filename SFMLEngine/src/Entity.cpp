#include "../headers/Entity.h"

SFENG::Entity::Entity()
	: m_Active(true)
{
	m_Components.reserve(32u);
	this->AddComponent<Transform>(Vec2f(0.0f, 0.0f), Vec2f(1.0f, 1.0f), 0.f);
	m_Active = true;
}

SFENG::Entity::Entity(const Entity& en)
{
	{	
		this->m_Components.reserve(en.m_Components.size());
		auto it = en.m_Components.begin();
		while (it != en.m_Components.end())
		{
			this->m_Components.push_back(*it);
			it++;
		}
	}
	{
		auto it = en.m_ComponentsMap.begin();
		while (it != en.m_ComponentsMap.end()) 
		{
			this->m_ComponentsMap.insert(*it);
			it++;
		}
	}
	m_Active = true;
}

void SFENG::Entity::PrintComponents()
{
	for (auto& comp : m_Components)
		comp->Print();
}

void SFENG::Entity::Draw(sf::RenderWindow& window)
{
	for (auto& comp : m_Components)
		comp->Draw(window);
}

void SFENG::Entity::Update(const sf::Time& time)
{
	for (auto& comp : m_Components)
		comp->Update(time);
}

void SFENG::Entity::HandleEvents(sf::Event& event)
{
	for (auto& comp : m_Components)
		comp->HandleEvents(event);
}

void SFENG::Entity::FixedUpdate(const sf::Time& time)
{
	for (auto& comp : m_Components)
		comp->FixedUpdate(time);
}

SFENG::Entity::~Entity()
{
	for(int i = m_Components.size() - 1; i >=0; i--)
	{
		if (m_Components[i] != nullptr)
			delete m_Components[i];
	}
	m_Components.clear();
	m_ComponentsMap.clear();
}