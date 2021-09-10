#pragma once
#include "../Component.h"
#include "SFML/Graphics.hpp"
#include "../../Vec2.h"

namespace SFENG {

	class Transform;

	namespace UI {

		class TextEnterHandler : public Component
		{
		public:
			TextEnterHandler();
			void SetFont(const std::string& fontName);
			bool Init() override;
			void HandleEvents(sf::Event& event) override;
			void Update(const sf::Time& elapsedTime) override;
			inline void SetMaxNumOfChars(int32_t num) { m_MaxCharacters = num; }
			inline void SetCharacterSize(uint32_t size) { text.setCharacterSize(size); m_MinSize.h = size + 10.0f; }
			inline void SetBoxColor(sf::Color clr) { m_Shape.setOutlineColor(clr); }
			inline void SetTextColor(sf::Color clr) { text.setFillColor(clr); }
			inline void Draw(sf::RenderWindow& window) override {
				window.draw(m_Shape, m_RenderState);
				window.draw(text, m_RenderState);
			}
			sf::Text text;
		private:
			void AddText(uint32_t value);
			void CenterText();
			bool ValidText(uint32_t unicode);
			std::string m_ActualText;
			Transform* m_Transform;
			sf::RectangleShape m_Shape;
			Vec2f m_MinSize;
			int32_t m_MaxCharacters;
		};
	}
}
