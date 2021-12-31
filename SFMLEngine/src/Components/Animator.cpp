#include "../../headers/Components/Animator.h"
#include "../../headers/Components/SpriteRenderer.h"
#include "../../headers/Entity.h"

namespace SFENG
{
	Animator::Animator()
		: m_ActiveAnimation("NULL"), m_Reset(false), m_SpriteRenderer(nullptr), m_LastAnimation("NULL")
	{
	}

	Animator::Animator(const Animator &a)
	{
		m_Reset = false;
		for (auto &anim : a.m_Animations)
		{
			m_Animations.insert(anim);
		}
		m_SpriteRenderer = a.m_SpriteRenderer;
		Component::Init();
	}

	void Animator::AttachSpriteRenderer(SpriteRenderer *sr)
	{
		m_SpriteRenderer = sr;
		for (auto &anim : m_Animations)
			anim.second.AttachSpriteRenderer(m_SpriteRenderer);
	}

	Animation *Animator::AddAnimation(const std::string &animName)
	{
		if (m_Animations.find(animName) == m_Animations.end())
		{
			Animation a(animName);
			m_Animations.insert({animName, a});
			m_Animations[animName].AttachSpriteRenderer(m_SpriteRenderer);
		}
		return &m_Animations[animName];
	}

	Animation *Animator::GetAnimation(const std::string &animName)
	{
		if (m_Animations.find(animName) != m_Animations.end())
			return &m_Animations[animName];
		else
			return nullptr;
	}

	void Animator::SetActiveAnimation(const std::string &animName)
	{
		m_ActiveAnimation = animName;
		if (m_LastAnimation != m_ActiveAnimation)
			m_Reset = true;
		m_LastAnimation = m_ActiveAnimation;
	}

	bool Animator::Init()
	{
		if (this->entity->HasComponent<SpriteRenderer>())
			m_SpriteRenderer = &this->entity->GetComponent<SpriteRenderer>();
		else
			m_SpriteRenderer = nullptr;
		return Component::Init();
	}

	void Animator::Update(const sf::Time &elapsedTime)
	{
		if (m_ActiveAnimation != "NULL")
		{
			Animation &animation = m_Animations[m_ActiveAnimation];
			if (m_Reset)
			{
				animation.Reset();
				m_Reset = false;
			}
			animation.Update(elapsedTime);
		}
	}

	void Animator::Print()
	{
		std::cout << "Animator Component\n";
		std::cout << "Has " << m_Animations.size() << " Animations\n";
	}

	Animator::~Animator()
	{
	}
}