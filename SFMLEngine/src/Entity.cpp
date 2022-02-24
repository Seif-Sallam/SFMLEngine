#include "Entity.h"
#include "BoxCollider.h"
namespace SFENG
{

	Entity::Entity(const std::string &name)
		: m_Active(true), m_Alive(true), m_Name(name)
	{
		m_Components.reserve(32u);
		this->AddComponent<Transform>(Vec2f(0.0f, 0.0f), Vec2f(1.0f, 1.0f), 0.f);
	}

	Entity::Entity(const Entity &en)
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

		int32_t index = en.m_Name.find("_");
		if (index == std::string::npos)
		{
			m_Name = en.m_Name + "_0";
		}
		else
		{
			std::string str = en.m_Name.substr(index + 1);
			int32_t digit = stoi(str);
			m_Name = en.m_Name.substr(0, index) + std::to_string(digit++);
		}
		m_Active = en.m_Active;
		m_Alive = true;
	}

	void Entity::PrintComponents()
	{
		for (auto &comp : m_Components)
			comp->Print();
	}

	void Entity::Draw(sf::RenderWindow &window)
	{
		for (auto &comp : m_Components)
			comp->Draw(window);
	}

	void Entity::Update(const sf::Time &time)
	{
		for (auto &comp : m_Components)
			comp->Update(time);
	}

	void Entity::HandleEvents(sf::Event &event)
	{
		for (auto &comp : m_Components)
			comp->HandleEvents(event);
	}

	void Entity::FixedUpdate(const sf::Time &time)
	{
		for (auto &comp : m_Components)
			comp->FixedUpdate(time);
	}

	void Entity::ImGuiLayer()
	{
		for (auto &comp : m_Components)
			comp->ImGuiLayer();
	}

	Entity::~Entity()
	{
		for (int i = m_Components.size() - 1; i >= 0; i--)
		{
			if (m_Components[i] != nullptr)
			{
				m_ComponentsMap.erase(typeid(*m_Components[i]));
				delete m_Components[i];
			}
		}
		m_Components.clear();
		m_ComponentsMap.clear();
	}
}