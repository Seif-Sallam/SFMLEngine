#pragma once
#include "Component.h"
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
		
		bool Init() override;
		void Draw(sf::RenderWindow& window) override;
		void Update(const sf::Time& elapsedTime) override;
		void FixedUpdate(const sf::Time& elapsedTime) override;
		void HandleEvents(sf::Event& event) override;
		void Print() override;
		

		Vec2f position;
		Vec2f size;
		float angle;
	};
}