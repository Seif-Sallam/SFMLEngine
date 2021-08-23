#include "../headers/EntityManager.h"

SFENG::EntityManager::EntityManager(const int32_t& initialSize)
{
	m_Entities.reserve(initialSize);
}

SFENG::Entity* SFENG::EntityManager::CloneEntity(SFENG::Entity* en)
{
	Entity* newEn =  new Entity(*en);
	if (newEn != nullptr)
		m_Entities.push_back(newEn);
	return newEn;
}

SFENG::EntityManager::EntityManager(const SFENG::EntityManager& em)
{
	this->m_Entities.reserve(em.m_Entities.size());
	auto it = em.m_Entities.begin();
	while (it != em.m_Entities.end())
	{
		this->m_Entities.push_back(*it);
		it++;
	}
}

SFENG::Entity* SFENG::EntityManager::MakeEntity()
{
	Entity* en = new Entity;
	if (en != nullptr)
		m_Entities.push_back(en);
	return en;
}

void SFENG::EntityManager::FixedUpdate(const sf::Time& time)
{
	for (auto& en : m_Entities)
		en->FixedUpdate(time);
}

void SFENG::EntityManager::HandleEvents(sf::Event& event)
{
	for (auto& en : m_Entities)
		en->HandleEvents(event);

}

void SFENG::EntityManager::Update(const sf::Time& time)
{
	for (auto& en : m_Entities)
		en->Update(time);
}

void SFENG::EntityManager::Draw(sf::RenderWindow& window)
{
	for (auto& en : m_Entities)
		en->Draw(window);
}

void SFENG::EntityManager::Refresh()
{
	GetInactive();
	CleanUpUnused();
}

void SFENG::EntityManager::GetInactive()
{
	auto it = m_Entities.begin();
	while (it != m_Entities.end()) {
		if(*it)
			RmEntity(it);
	}
}

void SFENG::EntityManager::CleanUpUnused()
{
	auto it = m_UnusedEntities.begin();
	while(it != m_UnusedEntities.end())
	{
		delete* it;
		it = m_UnusedEntities.erase(it);
	}

}

void SFENG::EntityManager::CleanUp()
{
	CleanUpUnused();
	for (int32_t i = 0; i < m_Entities.size(); i++)
	{
		delete m_Entities[i];
		m_Entities[i]= nullptr;
	}
	m_Entities.clear();
}

void SFENG::EntityManager::RmEntity(std::vector<Entity*>::iterator& it)
{
	if (it != m_Entities.end())
	{
		m_UnusedEntities.push_back(std::move(*it));
		it = m_Entities.erase(it);
	}
	else throw "Entity iterator was at the end!\n";
}

SFENG::EntityManager::~EntityManager()
{
	CleanUp();
}
