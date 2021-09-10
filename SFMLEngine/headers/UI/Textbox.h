#pragma once
#include <string>
#include "SFML/Graphics.hpp"
#include "../Vec2.h"
#include "UIElement.h"
#include "../Components/UI/TextEnterHandler.h"
namespace SFENG {
	namespace UI {
		
		class TextEnterHandler;
		class Textbox : public UIElement
		{
		public:
			Textbox(Entity* entity, Canvas* parentCanvas);
			inline void SetFont(const std::string& fontName) { m_TextEnterHandler->SetFont(fontName); }
		private:
			TextEnterHandler* m_TextEnterHandler;
			void Initialize() override;
		};
	}
}