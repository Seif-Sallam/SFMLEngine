#include "../../headers/Components/Controller.h"
#include "../../headers/Components/Transform.h"
#include "../../headers/Components/RigidBody2D.h"
#include "../../headers/Entity.h"

SFENG::Controller::Controller()
	: m_Transform(nullptr), m_RigidBody2D(nullptr), speed(0.f)
{
}

SFENG::Controller::~Controller()
{
}

void SFENG::Controller::SetRotation(float r)
{
	m_Transform->angle = r;
}

void SFENG::Controller::Rotate(float r)
{
	m_Transform->angle += r;
}

void SFENG::Controller::Scale(const Vec2f &factor)
{
	m_Transform->size.x *= factor.x;
	m_Transform->size.y *= factor.y;
}

void SFENG::Controller::Scale(float xFactor, float yFactor)
{
	m_Transform->size.x *= xFactor;
	m_Transform->size.y *= yFactor;
}

void SFENG::Controller::Scale(float factor)
{
	m_Transform->size *= factor;
}

void SFENG::Controller::Resize(float w, float h)
{
	m_Transform->size = {w, h};
}

void SFENG::Controller::Resize(const Vec2f &v)
{
	m_Transform->size = v;
}

void SFENG::Controller::Move(const Vec2f &v)
{
	m_Transform->position += v;
}

void SFENG::Controller::Move(float x, float y)
{
	m_Transform->position += {x, y};
}

void SFENG::Controller::SetPosition(const Vec2f &pos)
{
	m_Transform->position = pos;
}

void SFENG::Controller::SetPosition(float x, float y)
{
	m_Transform->position = {x, y};
}

bool SFENG::Controller::Init()
{
	m_Transform = &this->entity->GetComponent<Transform>();
	if (this->entity->HasComponent<RigidBody2D>())
	{
		m_RigidBody2D = &this->entity->GetComponent<RigidBody2D>();
	}
	return Component::Init();
}

void SFENG::Controller::Draw(sf::RenderWindow &window)
{
	return Component::Draw(window);
}

void SFENG::Controller::Update(const sf::Time &elapsedTime)
{
	return Component::Update(elapsedTime);
}

void SFENG::Controller::FixedUpdate(const sf::Time &elapsedTime)
{
	return Component::FixedUpdate(elapsedTime);
}

void SFENG::Controller::HandleEvents(sf::Event &event)
{
	return Component::HandleEvents(event);
}

void SFENG::Controller::Print()
{
	std::cout << "Controller Component\n";
	std::cout << "Speed: " << speed << '\n';
}