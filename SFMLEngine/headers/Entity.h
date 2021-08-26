#pragma once
#include <iostream>
#include <array>
#include <memory>
#include <vector>
#include <map>
#include <typeindex>
#include <typeinfo>
#include "SFML/Graphics.hpp"
#include "Transform.h"

namespace SFENG {
	class Entity {
	public:
		Entity(const std::string& name);

		Entity(const Entity& en);

		void PrintComponents();

		template<class Type, class... TypeArgs>
		Type& AddComponent(TypeArgs&&... args)
		{
			Type* comp = (std::move(new Type(std::forward<TypeArgs>(args)...)));

			m_Components.emplace_back(comp);

			comp->entity = this;
			if (comp->Init())
			{
				m_ComponentsMap[typeid(Type)] = comp;
				return *comp;
			}
			throw;
		}

		template<class Type>
		Type& GetCopmonent()
		{
			if (HasComponent<Type>())
			{
				auto& comp = m_ComponentsMap[typeid(Type)];
				if (comp->IsValid())
				{
					return *(dynamic_cast<Type*>(comp));
				}
			}
			throw "Component Is NOT valid OR doesn't exist";
		}

		template<class Type>
		bool HasComponent()
		{
			auto key = m_ComponentsMap.find(typeid(Type));
			return key != m_ComponentsMap.end();
		}

		inline bool IsAlive() const { return m_Alive; }
		inline bool IsActive() const { return m_Active; }
		inline void Deactivate() { m_Active = false; }
		inline bool Destory() { m_Alive = false; }

		void Draw(sf::RenderWindow& window);
		void Update(const sf::Time& time);
		void HandleEvents(sf::Event& event);
		void FixedUpdate(const sf::Time&);
		const std::string& GetName() const { return m_Name; }
		void SetName(const std::string& name) { m_Name = name; }
		~Entity();
	private:
		bool m_Active;
		bool m_Alive;
		std::string m_Name;
		std::vector<Component*> m_Components;
		std::map<std::type_index, Component*> m_ComponentsMap;
	};
}