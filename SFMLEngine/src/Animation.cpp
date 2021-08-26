#include "../headers/Animation.h"

SFENG::Animation::Animation(unsigned int frameWidth, unsigned int frameHeight)
	: m_FrameWidth(frameWidth), m_FrameHeight(frameHeight), m_FramePointer(0)
{
}

void SFENG::Animation::AddFrame(unsigned int index, sf::Time delay)
{
	sf::IntRect bounds;
	bounds.top = 0;
	bounds.height = m_FrameHeight;
	bounds.width = m_FrameWidth;
	bounds.left = index * m_FrameWidth;

	m_Frames.emplace_back(bounds, delay);
}

void SFENG::Animation::AddFrame(const sf::IntRect& rect, sf::Time delay)
{
	m_Frames.emplace_back(rect, delay);
}

const sf::IntRect& SFENG::Animation::GetFrame()
{
	m_OverlappedTime += m_Timer.getElapsedTime();

	while (m_OverlappedTime >= m_Frames[m_FramePointer % m_Frames.size()].delay)
	{
		m_OverlappedTime -= m_Frames[m_FramePointer % m_Frames.size()].delay;

		m_FramePointer++;
	}

	m_Timer.restart();

	return m_Frames[m_FramePointer % m_Frames.size()].bounds;
}