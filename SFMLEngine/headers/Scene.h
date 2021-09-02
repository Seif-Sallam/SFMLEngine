#pragma once
#include "box2d/box2d.h"
#include "SFML/Graphics.hpp"
#include "LifeCycleManager.h"

namespace SFENG {
	class Engine;
	class Scene {
	public:
		Scene(Engine& engine, b2World& phys)
			: m_Engine(engine)
			, m_PhysicsWorld(phys)
		{
			Main();
		}

		virtual ~Scene() = default;
		virtual void Main() {}

		inline void HandleEvents(sf::Event event) { m_LCManager.HandleEvents(event); }
		inline void Update(sf::Time elapsedTime) { m_LCManager.Update(elapsedTime); }
		inline void FixedUpdate(sf::Time elapsedTime) { m_LCManager.FixedUpdate(elapsedTime); }
		inline void Draw(sf::RenderWindow& window) { m_LCManager.Draw(window); }
		inline void Refresh() { m_LCManager.Refresh(); }

	protected:
		LifeCycleManager m_LCManager;
		Engine& m_Engine;
		b2World& m_PhysicsWorld;
	};
}