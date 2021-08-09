#include "../../headers/ECS/Transform.h"

using namespace SFENG;

Transform::Transform()
{
	position.Zero();
	scale.Zero();
	rotation = 0.f;
}

Transform::Transform(float x, float y)
{
	position.x = x;
	position.y = y;
	scale.One();
	rotation = 0.f;
}

Transform::Transform(Vec2f pos, Vec2f scale, float rotation)
{
	this->position = pos;
	this->scale = scale;
	this->rotation = rotation;
}
Transform::Transform(float x, float y, float scaleX, float scaleY, float rotation)
{
	this->position = Vec2f(x, y);
	this->scale = Vec2f(scaleX, scaleY);
	this->rotation = rotation;
}

bool Transform::Init()
{
	return Component::Init();
}

void Transform::Update(float deltaTime)
{

}

void Transform::Draw(sf::RenderWindow* window)
{
}

void Transform::HandleEvents(sf::Event* events)
{

}

void Transform::Translate(Vec2f pos, float dt)
{
	position += pos * dt;
}

