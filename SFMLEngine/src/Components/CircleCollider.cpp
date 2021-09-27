#include "../../headers/Components/CircleCollider.h"
#include "../../headers/Components/RigidBody2D.h"
#include "../../headers/Entity.h"
#include "../../headers/Engine.h"
#define _USE_MATH_DEFINES
#include <math.h>

SFENG::CircleCollider::CircleCollider()
	: m_PhysWorld(&SFENG::Engine::GetPhysicsWorld())
	, m_Body(nullptr)
	, m_Fixture(nullptr)
	, m_Transform(nullptr)
	, m_Radius(0.0f)
	, m_Friction(0.3f)
	, m_Density(1.0f)
	, m_IsSensor(false)
{
}

SFENG::CircleCollider::~CircleCollider()
{
	if (m_Fixture != nullptr)
		m_Body->DestroyFixture(m_Fixture);
}

void SFENG::CircleCollider::SetFriction(float f)
{
	m_Fixture->SetFriction(f);
	m_Friction = f;
}

void SFENG::CircleCollider::SetDensity(float d)
{
	m_Fixture->SetDensity(d);
	m_Density = d;
}

b2Body* SFENG::CircleCollider::GetBody()
{
	return m_Body;
}

b2Shape* SFENG::CircleCollider::GetShape()
{
	return m_Fixture->GetShape();
}

void SFENG::CircleCollider::SetSensor(bool s)
{
	m_IsSensor = s;
	m_Fixture->SetSensor(s);
}

bool SFENG::CircleCollider::Init()
{
	m_Transform = &this->entity->GetCopmonent<Transform>();
	if (this->entity->HasComponent<RigidBody2D>()) {
		RigidBody2D& rb = entity->GetCopmonent<RigidBody2D>();
		m_Body = rb.m_Body;
	}
	else
	{
		b2BodyDef bodyDef;
		bodyDef.position = m_Transform->position;
		bodyDef.angle = m_Transform->angle / 180.0f * M_PI;
		bodyDef.type = b2BodyType::b2_staticBody;
		m_Body = m_PhysWorld->CreateBody(&bodyDef);
	}
	CreateFixture();

	return Component::Init();
}

void SFENG::CircleCollider::Draw(sf::RenderWindow& window)
{
	return Component::Draw(window);
}

void SFENG::CircleCollider::Update(const sf::Time& elapsedTime)
{
	if (m_Radius != m_Transform->size.x)
	{
		CreateFixture();
	}
	return Component::Update(elapsedTime);
}

void SFENG::CircleCollider::FixedUpdate(const sf::Time& elapsedTime)
{
	return Component::FixedUpdate(elapsedTime);
}

void SFENG::CircleCollider::HandleEvents(sf::Event& event)
{
	return Component::HandleEvents(event);
}

void SFENG::CircleCollider::Print()
{
	std::cout << "CircleCollider Component\n";
	std::cout << "Friction: " << m_Friction << '\n';
	std::cout << "Density: " << m_Density << '\n';
	std::cout << "Sensor: " << ((m_IsSensor) ? "YES" : "NO") << '\n';
}

void SFENG::CircleCollider::CreateFixture()
{
	if (m_Fixture != nullptr)
	{
		m_Body->DestroyFixture(m_Fixture);
	}
	b2CircleShape shape;
	m_Radius = m_Transform->size.x;
	shape.m_radius = m_Radius;
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.density = m_Density;
	fixtureDef.friction = m_Friction;
	fixtureDef.isSensor = m_IsSensor;
	m_Fixture = m_Body->CreateFixture(&fixtureDef);
}