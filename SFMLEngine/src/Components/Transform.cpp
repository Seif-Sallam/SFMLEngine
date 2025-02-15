#include "Components/Transform.h"
#include "Components/RigidBody2D.h"
#include "Components/CircleCollider.h"
#include "Components/BoxCollider.h"
#include "Entity.h"

namespace SFENG
{

	Transform::Transform(const Vec2f &position, const Vec2f &size, const float &angle)
		: Component(), position(position), size(size), angle(angle)
	{
	}

	Transform::Transform(const Vec2f &position)
		: Component(), position(position), size(1.0f, 1.0f), angle(0.f)
	{
	}

	Transform::Transform(const Vec2f &position, const Vec2f &size)
		: Component(), position(position), size(size), angle(0.f)
	{
	}

	Transform::Transform()
		: Component(), position(0.0f, 0.0f), size(1.0f, 1.0f), angle(0.f)
	{
	}

	Transform::Transform(const Transform &t)
		: Component(), position(t.position), size(t.size), angle(t.angle)
	{
		Component::Init();
	}

	Transform::Transform(const Transform &&t)
		: Component(), position(t.position), size(t.size), angle(t.angle)
	{
		Component::Init();
	}

	Transform::~Transform()
	{
	}

	bool Transform::Init()
	{
		return Component::Init();
	}

	void Transform::Draw(sf::RenderWindow &window)
	{
		return Component::Draw(window);
	}

	void Transform::Update(const sf::Time &elapsedTime)
	{
		return Component::Update(elapsedTime);
	}

	void Transform::FixedUpdate(const sf::Time &elapsedTime)
	{
		return Component::FixedUpdate(elapsedTime);
	}

	void Transform::HandleEvents(sf::Event &event)
	{
		return Component::HandleEvents(event);
	}

	void Transform::Print()
	{
		std::cout << "Transform Component\n";
		std::cout << "Pos: " << position << "\n";
		std::cout << "m_Size: " << size << "\n";
		std::cout << "m_Angle: " << angle << "\n";
	}
}