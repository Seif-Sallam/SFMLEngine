#include "Scene.h"
#include "Engine.h"
SFENG::Scene::Scene(Engine &engine, bool isDefault)
	: m_Engine(engine), m_PhysicsWorld(Engine::GetPhysicsWorld())
{
	if (isDefault)
	{
		m_Engine.SetLCMToScene(this);
	}
}
