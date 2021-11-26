#include "../../headers/Components/Animation.h"
#include "../../headers/Components/SpriteRenderer.h"

SFENG::Animation::Animation()
	: m_Name("UNSET")
	, m_FramePointer(0u)
	, m_OverlappedTime(sf::Time::Zero)
	, m_Play(true)
	, m_Loop(false)
	, m_SpriteRender(nullptr)
{
}

SFENG::Animation::Animation(const std::string& name)
	: m_Name(name)
	, m_FramePointer(0u)
	, m_OverlappedTime(sf::Time::Zero)
	, m_Play(true)
	, m_Loop(false)
	, m_SpriteRender(nullptr)
{
}

SFENG::Animation::Animation(const Animation& a)
	: m_Name(a.m_Name)
	, m_FramePointer(0u)
	, m_OverlappedTime(sf::Time::Zero)
	, m_Play(a.m_Play)
	, m_Loop(a.m_Loop)
	, m_SpriteRender(a.m_SpriteRender)
{
	for (auto& frame : a.m_Frames)
		m_Frames.emplace_back(frame.bounds, frame.delay);
}

void SFENG::Animation::AddFrame(const sf::IntRect& rect, sf::Time delay)
{
	m_Frames.emplace_back(rect, delay);
}

void SFENG::Animation::SetName(const std::string& name)
{
	m_Name = name;
}

void SFENG::Animation::Play()
{
	m_Play = true;
}

void SFENG::Animation::Stop()
{
	m_Play = false;
}

void SFENG::Animation::Loop(bool v)
{
	m_Loop = v;
}

void SFENG::Animation::Reset()
{
	m_FramePointer = 0u;
}

void SFENG::Animation::AttachSpriteRenderer(SpriteRenderer* spriteRenderer)
{
	m_SpriteRender = spriteRenderer;
}

void SFENG::Animation::Update(const sf::Time& elapsedTime)
{
	if (m_Play)
	{
		if (m_Frames.size() > 0)
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
			const sf::IntRect& rect = m_Frames[m_FramePointer % m_Frames.size()].bounds;
			if (m_SpriteRender != nullptr) {
				m_SpriteRender->SetRect(rect);
			}
		}


		m_Timer.restart();
	}
}

void SFENG::Animation::Print()
{
	std::cout << "Animation Component\n";
	std::cout << "Frames Count: " << m_Frames.size() << '\n';
	std::cout << "Loop: " << ((m_Loop) ? "YES\n" : "NO\n");
}