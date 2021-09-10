#pragma once
#include "SFML/Graphics.hpp"
#include "../Vec2.h"
#include "UIElement.h"
#include <string>
#include "../Components/Component.h"

namespace SFENG {
	namespace UI {
		class Textbox : public UIElement
		{
		public:
			Textbox(Entity* entity, Canvas* parentCanvas);
			inline void SetFont(const std::string& fontName) { m_WriteTextComp->SetFont(fontName); }
		private:
			void Initialize() override;
			struct WriteText : public Component 
			{
				WriteText();
				void SetFont(const std::string& fontName);
				bool Init() override;
				void HandleEvents(sf::Event& event) override;
				void Update(const sf::Time& elapsedTime) override;
				inline void SetMaxNumOfChars(int32_t num) { m_MaxCharacters = num; }
				sf::Text text;
			private:
				void CenterText();
				bool ValidText(uint32_t unicode);
				std::string m_ActualText;
				Transform* m_Transform;
				sf::RectangleShape m_Shape;
				Vec2f m_MinSize;
				int32_t m_MaxCharacters;
			};
			WriteText* m_WriteTextComp;
		};
	}
}