#pragma once
#include <string>
#include <vector>
#include <map>
#include "Component.h"
#include "Vec2.h"

namespace SFENG
{
	class RigidBody2D;
	class Transform;
	class CircleCollider;
	class BoxCollider;

	class Controller : public Component
	{
		friend RigidBody2D;
		friend BoxCollider;
		friend CircleCollider;

	public:
		Controller();
		~Controller();

		void SetRotation(float r);
		void Rotate(float r);
		void Scale(const Vec2f &factor);
		void Scale(float xFactor, float yFactor);
		void Scale(float factor);
		void Resize(const Vec2f &v);
		void Resize(float w, float h);
		void Move(const Vec2f &v);
		void Move(float x, float y);
		void SetPosition(const Vec2f &pos);
		void SetPosition(float x, float y);
		bool Init() override;
		void Draw(sf::RenderWindow &window) override;
		void Update(const sf::Time &elapsedTime) override;
		void FixedUpdate(const sf::Time &elapsedTime) override;
		void HandleEvents(sf::Event &event) override;
		void Print() override;
		void SetRigidBody(RigidBody2D *rigidBody);
		void SetBoxCollider(BoxCollider *boxCollider);
		void SetCircleCollider(CircleCollider *circleCollider);

	private:
	public:
		float speed;
		RigidBody2D *m_RigidBody2D;
		BoxCollider *m_BoxCollider;
		CircleCollider *m_CircleCollider;

	private:
		Transform *m_Transform;
	};
}