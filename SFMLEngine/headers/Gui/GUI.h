#pragma once
#include "imgui.h"
#include "imgui-SFML.h"
#include <vector>
#include <string>
#include "GUIElement.h"

namespace SFENG {
	namespace UI {
		class GUI {
		public:
			static void GUIInit();
			template<class... Args>
			static void AddElement(GUIElement element, Args&&... args);
			static void UpdateGUI(sf::RenderWindow& window, sf::Time dt);
			static void EndGUI();
		private:
			GUI();
			std::vector<Element> m_Elements;
		};
	}
}