#pragma once
#include <string>
#include "SFML/Graphics.hpp"
#include "Vec2.h"
#include "UI/UIElement.h"
#include "Components/UI/TextEnterHandler.h"
#include "Components/UI/Selected.h"
#include "Components/Highlightable.h"

namespace SFENG {
	class Entity;
	namespace UI {
		class TextEnterHandler;
		class Canvas;

		class Textbox : public UIElement
		{
		public:
			Textbox(SFENG::Entity* entity, Canvas* parentCanvas);
			inline void SetFont(const std::string& fontName) { m_TextEnterHandler->SetFont(fontName); }

			virtual void Initialize() override;
		protected:

		private:
			TextEnterHandler* m_TextEnterHandler;
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