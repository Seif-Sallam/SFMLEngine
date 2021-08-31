#pragma once
#include "Entity.h"
#include <list>

namespace SFENG {
	//Life Cycle Manager
	class LifeCycleManager {
		LifeCycleManager(const int32_t& initialSize = 200);
		explicit LifeCycleManager(const LifeCycleManager& em);
		Entity* CloneEntity(Entity* en);
		Entity* MakeEntity(const std::string& name);
		Entity* GetEntity(const std::string& name) const;
		void FixedUpdate(const sf::Time& time);
		void HandleEvents(sf::Event& event);
		void Update(const sf::Time& time);
		void Refresh();
		void Draw(sf::RenderWindow& window);

		~LifeCycleManager();
	private:

		void GetInactive();
		void CleanUpUnused();
		void CleanUp();
		void RmEntity(std::vector<Entity*>::iterator& it);

		const std::string& AddEntityToMap(SFENG::Entity*& en, const std::string& name);

		std::vector<Entity*> m_Entities;
		std::list<Entity*> m_UnusedEntities;

		std::map<std::string, Entity*> m_EntitiesMap;
	};
}