﻿#include "../../headers/Components/Animator.h"

SFENG::Animator::Animator()
	: Component(), m_FramePointer(0)
	, m_OverlappedTime(sf::Time::Zero), m_Play(true), m_Loop(false), m_SpriteRender(0)
{
}

void SFENG::Animator::AddFrame(const sf::IntRect& rect, sf::Time delay)
{
	m_Frames.emplace_back(rect, delay);
}

void SFENG::Animator::Play()
{
	m_Play = true;
}

void SFENG::Animator::Stop()
{
	m_Play = false;
}

void SFENG::Animator::Loop(bool v)
{
	m_Loop = v;
}

void SFENG::Animator::AttachSpriteRenderer(SpriteRenderer* spriteRenderer)
{
	m_SpriteRender = spriteRenderer;
}

bool SFENG::Animator::Init()
{
	m_Timer.restart();
	return Component::Init();
}

void SFENG::Animator::Draw(sf::RenderWindow& window)
{
	return Component::Draw(window);
}

void SFENG::Animator::Update(const sf::Time& elapsedTime)
{
	if (m_Play)
	{
		m_OverlappedTime += m_Timer.getElapsedTime();

		while (m_OverlappedTime >= m_Frames[m_FramePointer % m_Frames.size()].delay)
		{
			m_OverlappedTime -= m_Frames[m_FramePointer % m_Frames.size()].delay;

			m_FramePointer++;
			if (m_FramePointer == m_Frames.size())
			{
				if (!m_Loop)
					Stop();
			}
		}

		m_Timer.restart();

		const sf::IntRect& rect = m_Frames[m_FramePointer % m_Frames.size()].bounds;
		if (m_SpriteRender != nullptr)
			m_SpriteRender->SetRect(rect);
	}
	return Component::Update(elapsedTime);
}

void SFENG::Animator::FixedUpdate(const sf::Time& elapsedTime)
{
	return Component::FixedUpdate(elapsedTime);
}

void SFENG::Animator::HandleEvents(sf::Event& event)
{
	return Component::HandleEvents(event);
}

void SFENG::Animator::Print()
{
	std::cout << "Animator Component\n";
	std::cout << "Frames Count: " << m_Frames.size() << '\n';
	std::cout << "Loop: " << ((m_Loop) ? "YES\n" : "NO\n");
}