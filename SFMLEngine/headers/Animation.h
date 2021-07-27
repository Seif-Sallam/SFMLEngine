#pragma once
#include "PCH.h"

namespace SFENG {
	class Animation {
	public:
		struct Frame {
			Frame(const sf::IntRect& bounds, sf::Time delay)
				: bounds(bounds), delay(delay)
			{}
			sf::IntRect bounds;
			sf::Time delay;
		};

		Animation(unsigned int frameWidth, unsigned int frameHeight);

		void AddFrame(unsigned int index, sf::Time delay);
		void AddFrame(const sf::IntRect& rect, sf::Time delay);
		const sf::IntRect& GetFrame();
	private:
		const unsigned int m_FrameWidth;
		const unsigned int m_FrameHeight;
		unsigned int m_FramePointer;
		sf::Clock m_Timer;
		sf::Time m_OverlappedTime;
		std::vector<Frame> m_Frames;
	};
}