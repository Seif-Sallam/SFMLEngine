#pragma once
#include "../Component.h"
#include "../Vec2.h"
namespace SFENG {
	class Transform : public Component
	{
	public:
		Transform(const Vec2f& position, const Vec2f& size, const float& rotation);
		Transform(const Vec2f& position);
		Transform(const Vec2f& position, const Vec2f& size);
		Transform();
		Transform(const Transform& t);
		Transform(const Transform&& t);
		~Transform();
		inline bool Init() override;
		inline void Draw(sf::RenderWindow& window) override;
		inline void Update(const sf::Time& elapsedTime) override;
		inline void FixedUpdate(const sf::Time& elapsedTime) override;
		inline void HandleEvents(sf::Event& event) override;
		inline void Print() override;
		Vec2f position;
		Vec2f size;
		float rotation;
	};
}