#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include <string>
#include <map>
#include "Vec2.h"

namespace SFENG {
	/// <summary>
	/// A Class made specifically to keep track of the FPS of the game
	///	and it shows it up on the top left of the screen at coordinates(0, 0).
	/// </summary>
	class FPSCounter
	{
	public:
		/// <summary>
		/// Constructor that needs the window to be present in it
		/// </summary>
		/// <param name="window">Render Window</param>
		FPSCounter(sf::RenderWindow* window);
		float Update();
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
