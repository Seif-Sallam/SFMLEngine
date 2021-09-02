#include "../headers/LifeCycleManager.h"

SFENG::LifeCycleManager::LifeCycleManager(const int32_t& initialSize)
{
	m_Entities.reserve(initialSize);
}

SFENG::Entity* SFENG::LifeCycleManager::CloneEntity(SFENG::Entity* en)
{
	Entity* newEn = new Entity(*en);
	if (newEn != nullptr) {
		m_Entities.push_back(newEn);
		newEn->SetName(AddEntityToMap(newEn, newEn->GetName()));
	}
	return newEn;
}

SFENG::LifeCycleManager::LifeCycleManager(const SFENG::LifeCycleManager& em)
{
	this->m_Entities.reserve(em.m_Entities.size());
	auto it = em.m_Entities.begin();
	while (it != em.m_Entities.end())
	{
		this->m_Entities.push_back(*it);
		it++;
	}
	for (auto i : em.m_EntitiesMap) {
		this->m_EntitiesMap.emplace(i);
	}
}

SFENG::Entity* SFENG::LifeCycleManager::CreateEntity(const std::string& name)
{
	Entity* en = new Entity(name);
	if (en != nullptr)
	{
		m_Entities.push_back(en);
		en->SetName(AddEntityToMap(en, name));
	}
	return en;
}

SFENG::Entity* SFENG::LifeCycleManager::GetEntity(const std::string& name) const
{
	if (m_EntitiesMap.find(name) == m_EntitiesMap.end())
		return nullptr;
	else
		return m_EntitiesMap.at(name);
}

void SFENG::LifeCycleManager::FixedUpdate(const sf::Time& time)
{
	for (auto& en : m_Entities)
		en->FixedUpdate(time);
}

void SFENG::LifeCycleManager::HandleEvents(sf::Event& event)
{
	for (auto& en : m_Entities)
		en->HandleEvents(event);
}

void SFENG::LifeCycleManager::Update(const sf::Time& time)
{
	for (auto& en : m_Entities)
		en->Update(time);
}

void SFENG::LifeCycleManager::Draw(sf::RenderWindow& window)
{
	sf::View currentView = window.getView();
	Vec2f min = currentView.getCenter() - currentView.getSize() / 2.0f;
	sf::IntRect viewRect = sf::IntRect(min.x, min.y, currentView.getSize().x, currentView.getSize().y);

	for (auto& en : m_Entities) {
		Transform& transform = en->GetCopmonent<Transform>();
		Vec2f minPos = transform.position - transform.size / 2.0f;
		sf::IntRect enRect = sf::IntRect(minPos.x, minPos.y, transform.size.x, transform.size.y);
		if (enRect.intersects(viewRect))
			en->Draw(window);
	}
}

void SFENG::LifeCycleManager::Refresh()
{
	GetInactive();
	CleanUpUnused();
}

void SFENG::LifeCycleManager::GetInactive()
{
	auto it = m_Entities.begin();
	while (it != m_Entities.end()) {
		if ((*it)->IsAlive() == false)
			RmEntity(it);
		else
		{
			it++;
		}
	}
}

void SFENG::LifeCycleManager::CleanUpUnused()
{
	auto it = m_UnusedEntities.begin();
	while (it != m_UnusedEntities.end())
	{
		m_EntitiesMap.erase((*it)->GetName());
		delete* it;
		it = m_UnusedEntities.erase(it);
	}
}

void SFENG::LifeCycleManager::CleanUp()
{
	CleanUpUnused();
	for (int32_t i = 0; i < m_Entities.size(); i++)
	{
		delete m_Entities[i];
		m_Entities[i] = nullptr;
	}
	m_Entities.clear();
	m_EntitiesMap.clear();
}

void SFENG::LifeCycleManager::RmEntity(std::vector<Entity*>::iterator& it)
{
	if (it != m_Entities.end())
	{
		m_UnusedEntities.push_back(std::move(*it));
		it = m_Entities.erase(it);
	}
	else throw "Entity iterator was at the end!\n";
}

const std::string& SFENG::LifeCycleManager::AddEntityToMap(SFENG::Entity*& en, const std::string& name)
{
	if (m_EntitiesMap.find(name) == m_EntitiesMap.end()) {
		m_EntitiesMap.insert({ name, en });
		return name;
	}
	else
	{
		int digit = 0;
		int index = name.find("_");
		std::string str = name;
		if (index != std::string::npos)
		{
			str = name + "_0";
			m_EntitiesMap.insert({ str, en });
			return str;
		}
		else
		{
			digit = stoi(name.substr(index + 1)) + 1;
			while (true)
			{
				str = name.substr(0, index);
				str += std::to_string(digit);
				if (m_EntitiesMap.find(str) == m_EntitiesMap.end())
				{
					m_EntitiesMap.insert({ str, en });
					return str;
					break;
				}
				else
				{
					digit++;
				}
			}
		}
	}
}

SFENG::LifeCycleManager::~LifeCycleManager()
{
	CleanUp();
}