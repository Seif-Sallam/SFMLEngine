#include "../headers/Scene.h"
#include "../headers/Engine.h"
SFENG::Scene::Scene(Engine& engine)
	: m_Engine(engine)
	, m_PhysicsWorld(Engine::GetPhysicsWorld())
{
}
