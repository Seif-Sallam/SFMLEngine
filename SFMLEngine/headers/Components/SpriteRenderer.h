#pragma once
#include "Component.h"
#include "Vec2.h"
#include "Transform.h"

namespace SFENG
{
	class SpriteRenderer : public Component
	{
	public:
		SpriteRenderer();
		~SpriteRenderer() = default;
		bool Init() override;
		void AttachTexture(const std::string &textureName);
		void SetRect(const sf::IntRect &rect);
		void Draw(sf::RenderWindow &window) override;
		void Update(const sf::Time &elapsedTime) override;
		void FixedUpdate(const sf::Time &elapsedTime) override;
		void HandleEvents(sf::Event &event) override;
		void Print() override;
		void SetScale(float x, float y);
		void SetScale(const Vec2f &scale);

	private:
		sf::Texture *m_Texture;
		std::string m_TextureName;
		sf::Sprite m_Sprite;
		Transform *m_Transform;
	};
}