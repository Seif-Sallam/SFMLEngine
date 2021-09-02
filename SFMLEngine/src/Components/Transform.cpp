#include "../../headers/Components/Transform.h"
#include "../../headers/Components/RigidBody2D.h"
#include "../../headers/Components/CircleCollider.h"
#include "../../headers/Components/BoxCollider.h"
#include "../../headers/Entity.h"

SFENG::Transform::Transform(const Vec2f& position, const Vec2f& size, const float& angle)
	: Component(), position(position), size(size), angle(angle)
{
}

SFENG::Transform::Transform(const Vec2f& position)
	: Component(), position(position), size({ 1.f, 1.f }), angle(0.f)
{
}

SFENG::Transform::Transform(const Vec2f& position, const Vec2f& size)
	: Component(), position(position), size(size), angle(0.f)
{
}

SFENG::Transform::Transform()
	: Component(), position({ 0.0f, 0.0f }), size({ 1.0f, 1.0f }), angle(0.f)
{
}

SFENG::Transform::Transform(const Transform& t)
	: Component(), position(t.position), size(t.size), angle(t.angle)
{
	Component::Init();
}

SFENG::Transform::Transform(const Transform&& t)
	: Component(), position(t.position), size(t.size), angle(t.angle)
{
	Component::Init();
}

SFENG::Transform::~Transform()
{
}


bool SFENG::Transform::Init()
{
	return Component::Init();
}

void SFENG::Transform::Draw(sf::RenderWindow& window)
{
	return Component::Draw(window);
}

void SFENG::Transform::Update(const sf::Time& elapsedTime)
{
	return Component::Update(elapsedTime);
}

void SFENG::Transform::FixedUpdate(const sf::Time& elapsedTime)
{
	return Component::FixedUpdate(elapsedTime);
}

void SFENG::Transform::HandleEvents(sf::Event& event)
{
	return Component::HandleEvents(event);
}

void SFENG::Transform::Print()
{
	std::cout << "Transform Component\n";
	std::cout << "Pos: " << position << "\n";
	std::cout << "m_Size: " << size << "\n";
	std::cout << "m_Angle: " << angle << "\n";
}