#pragma once
#include "Component.h"
#include "box2d/box2d.h"
#include "Transform.h"

namespace SFENG {
	class RigidBody2D;
	class BoxCollider : public Component
	{
		friend RigidBody2D;
	public:
		BoxCollider(b2World* world);
		~BoxCollider();

		void SetFriction(float f);
		void SetDensity(float d);
		b2Body* GetBody();
		b2Shape* GetShape();
		void SetSize(const Vec2f& v);
		void SetSensor(bool s);
		bool Init() override;
		void Draw(sf::RenderWindow& window) override;
		void Update(const sf::Time& elapsedTime) override;
		void FixedUpdate(const sf::Time& elapsedTime) override;
		void HandleEvents(sf::Event& event) override;
		void Print() override;

	private:

		void CreateFixture();
		b2Body* m_Body;
		b2World* m_PhysWorld;
		b2Fixture* m_Fixture;
		Transform* m_Transform;
		Vec2f m_CurrentSize;
		float m_Friction;
		float m_Density;
		bool m_IsSensor;
	};
}