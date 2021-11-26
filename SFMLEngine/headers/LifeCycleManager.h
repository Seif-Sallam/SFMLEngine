#pragma once
#include "Entity.h"
#include <list>

namespace SFENG {
	/// <summary>
	/// Life Cycle Manager is the main class that creates Entities, clones Entities and maintains their life cycles.
	/// An Entity is removed when it is considered not valid.
	/// Every entity is also saved with a string attached to it.
	/// It also is responsible for updaing, handling events, and drawing every entity efficiently.
	/// </summary>
	class LifeCycleManager {
	public:
		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="initialSize">Initial Size of the vector of Entities</param>
		LifeCycleManager(const int32_t& initialSize = 200);
		
		/// <summary>
		/// Copy Constructor
		/// </summary>
		/// <param name="em">Other Life Cycle Manager</param>
		explicit LifeCycleManager(const LifeCycleManager& em);

		/// <summary>
		/// Clones the Entity and adds it to the vector.
		/// </summary>
		/// <param name="en">Other Entity</param>
		/// <returns>A pointer to the newly created entity</returns>
		Entity* CloneEntity(Entity* en);

		/// <summary>
		/// Create Entity. Do not create an Entity from outside class.
		/// </summary>
		/// <param name="name">The name of the Entity</param>
		/// <returns>A pointer to the Entity just created</returns>
		Entity* CreateEntity(const std::string& name);

		/// <summary>
		/// </summary>
		/// <param name="name">The name of the entity</param>
		/// <returns>A pointer to the Entity of that name</returns>
		Entity* GetEntity(const std::string& name) const;
		
		/// <summary>
		/// The Fixed Update function that calls FixedUpdate in all Entities.
		/// </summary>
		/// <param name="time">Elapsed Time </param>
		void FixedUpdate(const sf::Time& time);

		/// <summary>
		/// Handle Events function that calls HandleEvents in all Entities.
		/// </summary>
		/// <param name="event"></param>
		void HandleEvents(sf::Event& event);

		/// <summary>
		/// Update function that calls Update in all Entities.
		/// </summary>
		/// <param name="time">Elapsed Time</param>
		void Update(const sf::Time& time);

		/// <summary>
		/// Function that is called to remove the unused functions
		/// </summary>
		void Refresh();

		/// <summary>
		/// Draws all the Entities.
		/// </summary>
		/// <param name="window"></param>
		void Draw(sf::RenderWindow& window);

		~LifeCycleManager();
	private:
		void GetDeadEntities();
		void CleanUpUnused();
		void CleanUp();
		void RmEntity(std::vector<Entity*>::iterator& it);

		std::string AddEntityToMap(SFENG::Entity*& en, const std::string& name);

		std::vector<Entity*> m_Entities;
		std::list<Entity*> m_UnusedEntities;

		std::map<std::string, Entity*> m_EntitiesMap;
		std::map<std::string, int32_t> m_EntitiesUsedNums;
	};
}