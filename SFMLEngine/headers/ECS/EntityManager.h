#pragma once
#include <vector>
#include <memory>
#include "Entity.h"
namespace SFENG {
	class EntityManager
	{
	public:
		EntityManager() = default;
		~EntityManager();

		void Draw(sf::RenderWindow* window);
		void Update(float deltaTime);
		void Refresh();
		void HandleEvents(sf::Event* event);
		Entity* MakeEntity();
		void EraseEntity(Entity* en);
		Entity* cloneEntity(Entity* en);

	private:
		void CleanUpUnused();
		void CleanUp();
		std::vector<Entity*> m_Entities;
	};
}