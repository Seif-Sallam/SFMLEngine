#include "../../headers/ECS/EntityManager.h"
using namespace SFENG;

EntityManager::~EntityManager()
{
}

void EntityManager::Draw(sf::RenderWindow* window)
{
	for (auto en : m_Entities)
		en->Draw(window);
}

void EntityManager::Update(float deltaTime)
{
	for (auto en : m_Entities)
		en->Update(deltaTime);
}

void EntityManager::CleanUpUnused()
{
	for(int32_t i = 0; i < m_Entities.size(); i++)
	{
		if (!m_Entities[i]->IsActive())
		{
			delete m_Entities[i];
			m_Entities[i] = nullptr;
		}
	}

	while (true)
	{
		std::vector<Entity*>::iterator it = m_Entities.begin();
		it = std::find(std::begin(m_Entities), std::end(m_Entities), nullptr);
		if (it != m_Entities.end())
		{
			m_Entities.erase(it);
#ifdef _DEBUG
			std::cout << "Deleting Entity\n";
#endif // _DEBUG
		}
		else
			break;
	}
}

void EntityManager::CleanUp()
{
	for (int32_t i = 0; i < m_Entities.size(); i++)
	{
		delete m_Entities[i];
		m_Entities[i] = nullptr;
	}
	m_Entities.clear();
}

void EntityManager::Refresh()
{
	CleanUpUnused();
}

void EntityManager::HandleEvents(sf::Event* event)
{
	for (auto& en : m_Entities)
		en->HandleEvents(event);
}

SFENG::Entity* EntityManager::MakeEntity()
{
	Entity* en = new Entity;
	if (en != nullptr)
		m_Entities.push_back(en);
	return en;
}

void EntityManager::EraseEntity(Entity* en)
{
	auto it = std::find(m_Entities.begin(), m_Entities.end(), en);
	if(it != std::end(m_Entities))
		m_Entities.erase(it);
}

SFENG::Entity* EntityManager::cloneEntity(Entity* en)
{
	return nullptr;
}
