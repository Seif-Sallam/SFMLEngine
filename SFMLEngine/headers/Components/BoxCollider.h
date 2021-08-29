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

		inline void SetFriction(float f);
		inline void SetDensity(float d);
		inline b2Body* GetBody();
		inline b2Shape* GetShape();
		inline void SetSensor(bool s);
		inline bool Init() override;
		inline void Draw(sf::RenderWindow& window) override;
		inline void Update(const sf::Time& elapsedTime) override;
		inline void FixedUpdate(const sf::Time& elapsedTime) override;
		inline void HandleEvents(sf::Event& event) override;
		inline void Print() override;

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