#pragma once
#include "Component.h"
#include "../Vec2.h"
#include <vector>
#include "Transform.h"
#include "box2d/box2d.h"

namespace SFENG {
	class CircleCollider;
	class BoxCollider;
	class RigidBody2D : public Component {
		friend CircleCollider;
		friend BoxCollider;
	public:
		RigidBody2D() = delete;
		RigidBody2D(const RigidBody2D&) = delete;
		RigidBody2D(b2World* world);
		~RigidBody2D();
		inline void SetBodyType(const b2BodyType& type);
		inline b2Body* GetBody();
		inline b2Fixture* CreateFixture(const b2Shape* shape, float dinsety);
		inline b2Fixture* CreateFixture(const b2FixtureDef* def);
		inline const Vec2f& GetPosition() const;
		inline const float& GetAngle() const;
		inline bool Init() override;
		inline void Draw(sf::RenderWindow& window) override;
		inline void Update(const sf::Time& elapsedTime) override;
		inline void FixedUpdate(const sf::Time& elapsedTime) override;
		inline void HandleEvents(sf::Event& event) override;
		inline void Print() override;
	private:
		b2World* m_PhysWorld;
		b2Body* m_Body;
		Transform* m_Transform;

	};
}