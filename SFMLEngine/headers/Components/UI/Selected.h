#pragma once
#include "../Component.h"
#include "SFML/Graphics.hpp"
#include "../../Vec2.h"
#include "../../Mouse.h"

namespace SFENG {
	class Tranform;
	class Highlightable;
	namespace UI {
		class Selected : public Component 
		{
		public:
			bool Init() override;
			void HandleEvents(sf::Event& event) override;
			inline bool IsPressed() { return m_Pressed; }
		private:
			Highlightable* m_Highlightable;
			bool m_Pressed = false;
		};
	}
}
