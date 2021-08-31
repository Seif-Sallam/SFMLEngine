#include "../../headers/Components/Controller.h"
#include "../../headers/Components/Transform.h"
#include "../../headers/Components/RigidBody2D.h"
#include "../../headers/Entity.h"

SFENG::Controller::Controller()
	: m_Transform(nullptr)
	, m_RigidBody2D(nullptr)
	, speed(0.f)
{
}

SFENG::Controller::~Controller()
{
}

inline void SFENG::Controller::SetRotation(float r)
{
	m_Transform->rotation = r;
}

inline void SFENG::Controller::Rotate(float r)
{
	m_Transform->rotation += r;
}

inline void SFENG::Controller::Scale(const Vec2f& factor)
{
	m_Transform->size.x *= factor.x;
	m_Transform->size.y *= factor.y;
}

inline void SFENG::Controller::Scale(float xFactor, float yFactor)
{
	m_Transform->size.x *= xFactor;
	m_Transform->size.y *= yFactor;
}

inline void SFENG::Controller::Scale(float factor)
{
	m_Transform->size *= factor;
}

inline void SFENG::Controller::Resize(float w, float h)
{
	m_Transform->size = { w, h };
}

inline void SFENG::Controller::Resize(const Vec2f& v)
{
	m_Transform->size = v;
}

inline void SFENG::Controller::Move(const Vec2f& v)
{
	m_Transform->position += v;
}

inline void SFENG::Controller::Move(float x, float y)
{
	m_Transform->position += { x, y };
}

inline void SFENG::Controller::SetPosition(const Vec2f& pos)
{
	m_Transform->position = pos;
}

inline void SFENG::Controller::SetPosition(float x, float y)
{
	m_Transform->position = { x, y };
}

inline bool SFENG::Controller::Init()
{
	m_Transform = &this->entity->GetCopmonent<Transform>();
	if (this->entity->HasComponent<RigidBody2D>())
	{
		m_RigidBody2D = &this->entity->GetCopmonent<RigidBody2D>();
	}
	return Component::Init();
}

inline void SFENG::Controller::Draw(sf::RenderWindow& window)
{
	return Component::Draw(window);
}

inline void SFENG::Controller::Update(const sf::Time& elapsedTime)
{
	return Component::Update(elapsedTime);
}

inline void SFENG::Controller::FixedUpdate(const sf::Time& elapsedTime)
{
	return Component::FixedUpdate(elapsedTime);
}

inline void SFENG::Controller::HandleEvents(sf::Event& event)
{
	return Component::HandleEvents(event);
}

inline void SFENG::Controller::Print()
{
	std::cout << "Controller Component\n";
	std::cout << "Speed: " << speed << '\n';
}
