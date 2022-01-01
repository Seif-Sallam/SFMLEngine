#include "LifeCycleManager.h"

namespace SFENG
{
	LifeCycleManager *LCM::s_OnGoingLCM = nullptr;

	LifeCycleManager::LifeCycleManager(const int32_t &initialSize)
	{
		// m_Entities.reserve(initialSize);
	}

	Entity *LifeCycleManager::CloneEntity(Entity *en)
	{
		Entity *newEn = new Entity(*en);
		if (newEn != nullptr)
		{
			m_Entities.push_back(newEn);
			newEn->SetName(AddEntityToMap(newEn, newEn->GetName()));
		}
		return newEn;
	}

	LifeCycleManager::LifeCycleManager(const LifeCycleManager &em)
	{
		// this->m_Entities.reserve(em.m_Entities.size());
		auto it = em.m_Entities.begin();
		while (it != em.m_Entities.end())
		{
			this->m_Entities.push_back(*it);
			it++;
		}
		for (auto &i : em.m_EntitiesMap)
		{
			this->m_EntitiesMap.emplace(i);
		}
	}

	Entity *LifeCycleManager::CreateEntity(const std::string &name)
	{
		Entity *en = new Entity(name);
		if (en != nullptr)
		{
			m_Entities.push_back(en);
			en->SetName(AddEntityToMap(en, name));
		}
		return en;
	}

	Entity *LifeCycleManager::GetEntity(const std::string &name) const
	{
		if (m_EntitiesMap.find(name) == m_EntitiesMap.end())
			return nullptr;
		else
			return m_EntitiesMap.at(name);
	}

	void LifeCycleManager::FixedUpdate(const sf::Time &time)
	{
		for (auto &en : m_Entities)
			if (en->IsActive())
				en->FixedUpdate(time);
	}

	void LifeCycleManager::HandleEvents(sf::Event &event)
	{
		for (auto &en : m_Entities)
			if (en->IsActive())
				en->HandleEvents(event);
	}

	void LifeCycleManager::Update(const sf::Time &time)
	{
		for (auto &en : m_Entities)
			if (en->IsActive())
				en->Update(time);
	}

	void LifeCycleManager::ImGuiLayer()
	{
		for (auto &en : m_Entities)
			if (en->IsActive())
				en->ImGuiLayer();
	}

	void LifeCycleManager::Draw(sf::RenderWindow &window)
	{
		sf::View currentView = window.getView();
		Vec2f min = currentView.getCenter() - currentView.getSize() / 2.0f;
		sf::IntRect viewRect = sf::IntRect(min.x, min.y, currentView.getSize().x, currentView.getSize().y);

		for (auto &en : m_Entities)
		{
			Transform &transform = en->GetComponent<Transform>();
			Vec2f minPos = transform.position - transform.size / 2.0f;
			sf::IntRect enRect = sf::IntRect(minPos.x, minPos.y, transform.size.x, transform.size.y);
			if (enRect.intersects(viewRect))
				en->Draw(window);
		}
	}

	void LifeCycleManager::Refresh()
	{
		GetDeadEntities();
		CleanUpUnused();
	}

	void LifeCycleManager::GetDeadEntities()
	{
		auto it = m_Entities.begin();
		while (it != m_Entities.end())
		{
			if ((*it)->IsAlive() == false)
				RmEntity(it);
			else
				it++;
		}
	}

	void LifeCycleManager::CleanUpUnused()
	{
		auto it = m_UnusedEntities.begin();
		while (it != m_UnusedEntities.end())
		{
			m_EntitiesMap.erase((*it)->GetName());
			delete *it;
			it = m_UnusedEntities.erase(it);
		}
	}

	void LifeCycleManager::CleanUp()
	{
		CleanUpUnused();
		for (auto &entity : m_Entities)
		{
			delete entity;
			entity = nullptr;
		}
		m_Entities.clear();
		m_EntitiesMap.clear();
	}

	void LifeCycleManager::RmEntity(std::list<Entity *>::iterator &it)
	{
		if (it != m_Entities.end())
		{
			m_UnusedEntities.push_back(std::move(*it));
			it = m_Entities.erase(it);
		}
		else
			return;
	}

	std::string LifeCycleManager::AddEntityToMap(Entity *&en, const std::string &name)
	{
		if (m_EntitiesMap.find(name) == m_EntitiesMap.end())
		{
			m_EntitiesMap.insert({name, en});
			m_EntitiesUsedNums.insert({name, 0});
			return name;
		}
		else
		{
			int32_t &num = m_EntitiesUsedNums[name];
			num++;
			std::string newName = name + std::to_string(num);
			m_EntitiesMap.insert({newName, en});
			return newName;
		}
	}

	LifeCycleManager::~LifeCycleManager()
	{
		CleanUp();
	}

	Entity *LCM::InstantiateObject(const std::string &name)
	{
		if (s_OnGoingLCM)
		{
			return LCM::s_OnGoingLCM->CreateEntity(name);
		}
		else
			return nullptr;
	}
}