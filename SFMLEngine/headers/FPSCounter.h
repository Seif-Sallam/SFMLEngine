#pragma once
#include "PCH.h"
namespace SFENG {
	class FPSCounter
	{
	public:
		FPSCounter(sf::RenderWindow* window);
		void Update();

		void Draw(sf::RenderStates states = sf::RenderStates::Default);

	private:
		sf::RenderWindow* m_Window;
		sf::Text m_Text;

		sf::Clock m_FPSTimer;
		sf::Clock m_DelayTimer;

		float m_FPS;
		uint32_t m_FrameCounter;
	};
}
