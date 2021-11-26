#pragma once
#include "SFML/Graphics.hpp"
#include "UIElement.h"

namespace SFENG {
	namespace UI {
		class Button : public UIElement {
		public:
			Button(Entity* entity, Canvas* parentCanvas);
			
		private:
			void Initialize() override;
			
		};
	}
}