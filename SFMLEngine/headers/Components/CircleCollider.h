#pragma once
#include "Component.h"
#include "box2d/box2d.h"
#include "Transform.h"
#include <list>

namespace SFENG
{
	class RigidBody2D;
	class Controller;
	class CircleCollider : public Component
	{
		friend RigidBody2D;
		friend Controller;

	public:
		CircleCollider();
		~CircleCollider();

		void SetFriction(float f);
		void SetDensity(float d);
		b2Body *GetBody();
		b2Shape *GetShape();
		void SetSensor(bool s);
		bool Init() override;
		void Draw(sf::RenderWindow &window) override;
		void Update(const sf::Time &elapsedTime) override;
		void FixedUpdate(const sf::Time &elapsedTime) override;
		void HandleEvents(sf::Event &event) override;
		void Print() override;
		std::list<Entity *> GetCollidingItems();

	private:
		void CreateFixture();

	private:
		b2World *m_PhysWorld;
		b2Body *m_Body;
		b2Fixture *m_Fixture;
		Transform *m_Transform;
		float m_Radius;
		float m_Friction;
		float m_Density;
		bool m_IsSensor;
	};
}