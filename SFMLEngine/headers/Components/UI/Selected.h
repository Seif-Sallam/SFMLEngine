#pragma once
#include "SFML/Graphics.hpp"
#include "Components/Component.h"
#include "Vec2.h"
#include "Mouse.h"

namespace SFENG
{
	class Transform;
	class Highlightable;
	namespace UI
	{
		class Selected : public Component
		{
		public:
			bool Init() override;
			void HandleEvents(sf::Event &event) override;
			inline bool IsPressed() { return m_Pressed; }

		private:
			Highlightable *m_Highlightable;
			bool m_Pressed = false;
		};
	}
}
