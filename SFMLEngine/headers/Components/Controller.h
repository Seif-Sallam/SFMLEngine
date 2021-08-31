#pragma once
#include <string>
#include <vector>
#include <map>
#include "Component.h"
#include "../Vec2.h"

namespace SFENG {
	class RigidBody2D;
	class Transform;

	class Controller : public Component
	{
		friend RigidBody2D;
	public:
		Controller();
		~Controller();

		inline void SetRotation(float r);
		inline void Rotate(float r);
		inline void Scale(const Vec2f& factor);
		inline void Scale(float xFactor, float yFactor);
		inline void Scale(float factor);
		inline void Resize(const Vec2f& v);
		inline void Resize(float w, float h);
		inline void Move(const Vec2f& v);
		inline void Move(float x, float y);
		inline void SetPosition(const Vec2f& pos);
		inline void SetPosition(float x, float y);

		inline bool Init() override;
		inline void Draw(sf::RenderWindow& window) override;
		inline void Update(const sf::Time& elapsedTime) override;
		inline void FixedUpdate(const sf::Time& elapsedTime) override;
		inline void HandleEvents(sf::Event& event) override;
		inline void Print() override;
	private:

	public:
		float speed;
		RigidBody2D* m_RigidBody2D;
	private:
		Transform* m_Transform;
	};

}