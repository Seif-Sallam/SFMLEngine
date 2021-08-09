#pragma once
#include "ECS.h"
#include "Transform.h"
#include "SFML/Graphics.hpp"
#include <map>
#include <typeindex>
namespace SFENG {
	class Entity
	{
	public:
		Entity()
			: m_ComponentsMap()
		{
			this->AddComponent<Transform>(Vec2f(0.0f, 0.0f), Vec2f(1.0f, 1.0f), 0.0f);
			m_Active = true;
		}

		void PrintComponents()
		{
			for (auto& comp : m_Components)
				comp->Print();
		}

		template<class T, class... TArgs>
		T& AddComponent(TArgs&&... args)
		{
			T* comp = (std::move(new T(std::forward<TArgs>(args)...)));

			m_Components.emplace_back(comp);
			comp->entity = this;
			if (comp->Init())
			{
				m_ComponentsMap[typeid(T)] = comp;
				return *comp;
			}
			throw;
		}

		template <class T>
		T& GetComponent() {
			auto component = m_ComponentsMap[typeid(T)];
			if (component->IsValid())
			{
				return *(dynamic_cast<T*>(component));
			}
			throw;
		}

		template<class T>
		bool HasComponent() {
			auto key = m_ComponentsMap.find(typeid(T));
			return key != m_ComponentsMap.end();
		}


		bool IsActive() const {
			return m_Active;
		}

		void Destory() {
			m_Active = false;
		}

		void Draw(sf::RenderWindow* window) {
			for (uint16_t i = 0; i < m_Components.size(); i++)
				m_Components[i]->Draw(window);
		}
		void Update(float deltaTime) {
			for (uint16_t i = 0; i < m_Components.size(); i++)
				m_Components[i]->Update(deltaTime);
		}

		void HandleEvents(sf::Event* event) {
			for (auto& comp : m_Components)
				comp->HandleEvents(event);
		}

		~Entity()
		{
			//Deleteing the componants: 
			std::cout << "Deleting Componants\n";
			for (int i = 0; i < m_Components.size(); i++)
			{
				if (m_Components[i] != nullptr) {
					std::cout << "Componant: "; m_Components[i]->Print();
					delete m_Components[i];
					m_Components[i] = nullptr;
				}
				else {
					std::cout << "Error a componant is a nullptr\n";
				}
			}
			m_ComponentsMap.clear();
			m_Components.clear();
			std::cout << "Done deleting Componants\n";
		}
	private:
		std::vector<Component*> m_Components;
		bool m_Active;
		std::map<std::type_index, Component*> m_ComponentsMap;
	};
}