#include "../headers/Transform.h"

SFENG::Transform::Transform(const Vec2f& position, const Vec2f& size, const float& rotation)
	: Component(), position(position), size(size), rotation(rotation)
{
}

SFENG::Transform::Transform(const Vec2f& position)
	: Component(), position(position), size({ 1.f, 1.f }), rotation(0.f)
{
}

SFENG::Transform::Transform(const Vec2f& position, const Vec2f& size)
	: Component(), position(position), size(size), rotation(0.f)
{
}

SFENG::Transform::Transform()
	: Component(), position({ 0.0f, 0.0f }), size({ 1.0f, 1.0f }), rotation(0.f)
{
}

SFENG::Transform::Transform(const Transform& t)
	: Component(), position(t.position), size(t.size), rotation(t.rotation)
{
}

SFENG::Transform::Transform(const Transform&& t)
	: Component(), position(t.position), size(t.size), rotation(t.rotation)
{
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