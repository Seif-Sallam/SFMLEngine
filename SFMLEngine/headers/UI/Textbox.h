#pragma once
#include <string>
#include "SFML/Graphics.hpp"
#include "../Vec2.h"
#include "UIElement.h"
#include "../Components/UI/TextEnterHandler.h"
#include "../Components/UI/Selected.h"
#include "../Components/Highlightable.h"
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
			bool m_Active;
			class TextBoxSelection : public Component {
			public:
				bool Init() override;
				void HandleEvents(sf::Event& event) override;
			private:
				Selected* m_SelectedComp;
				TextEnterHandler* m_TxtEnterHandler;
			};
		};
	}
}