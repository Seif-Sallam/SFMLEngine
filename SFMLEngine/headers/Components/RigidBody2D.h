#pragma once
#include <vector>
#include "Component.h"
#include "box2d/box2d.h"
#include "Vec2.h"

namespace SFENG
{
	class CircleCollider;
	class BoxCollider;
	class Transform;
	class Controller;
	class RigidBody2D : public Component
	{
		friend CircleCollider;
		friend BoxCollider;
		friend Controller;

	public:
		RigidBody2D(const RigidBody2D &) = delete;
		RigidBody2D();
		~RigidBody2D();
		void SetBodyType(const b2BodyType &type);
		b2Body *GetBody();
		b2Fixture *CreateFixture(const b2Shape *shape, float dinsety);
		b2Fixture *CreateFixture(const b2FixtureDef *def);
		void ApplyForce(const Vec2f &force);
		Vec2f GetPosition();
		void SetPosition(const Vec2f &v);
		float GetAngle();
		bool Init() override;
		void Draw(sf::RenderWindow &window) override;
		void Update(const sf::Time &elapsedTime) override;
		void FixedUpdate(const sf::Time &elapsedTime) override;
		void HandleEvents(sf::Event &event) override;
		void Print() override;

	private:
		void DeleteFixtures();
		b2World *m_PhysWorld;
		b2Body *m_Body;
		Transform *m_Transform;
		Vec2f m_OldBodyPos;
		float m_OldAngle;
	};
}