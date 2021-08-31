#include "../../headers/Components/BoxCollider.h"
#include "../../headers/Components/RigidBody2D.h"
#include "../../headers/Entity.h"

SFENG::BoxCollider::BoxCollider(b2World* world)
	: m_PhysWorld(world)
	, m_Body(nullptr)
	, m_Fixture(nullptr)
	, m_Transform(nullptr)
	, m_CurrentSize(Vec2f(0.0f, 0.0f))
	, m_Friction(0.3f)
	, m_Density(1.0f)
	, m_IsSensor(false)
{
}

SFENG::BoxCollider::~BoxCollider()
{
	if (m_Fixture != nullptr)
		m_Body->DestroyFixture(m_Fixture);
}

void SFENG::BoxCollider::SetFriction(float f)
{
	m_Fixture->SetFriction(f);
	m_Friction = f;
}

void SFENG::BoxCollider::SetDensity(float d)
{
	m_Fixture->SetDensity(d);
	m_Density = d;
}

b2Body* SFENG::BoxCollider::GetBody()
{
	return m_Body;
}

b2Shape* SFENG::BoxCollider::GetShape()
{
	return m_Fixture->GetShape();
}

void SFENG::BoxCollider::SetSensor(bool s)
{
	m_IsSensor = s;
	m_Fixture->SetSensor(s);
}

bool SFENG::BoxCollider::Init()
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
		bodyDef.angle = m_Transform->angle;
		bodyDef.type = b2BodyType::b2_staticBody;
		m_Body = m_PhysWorld->CreateBody(&bodyDef);
	}
	CreateFixture();

	return Component::Init();
}

void SFENG::BoxCollider::Draw(sf::RenderWindow& window)
{
	return Component::Draw(window);
}

void SFENG::BoxCollider::Update(const sf::Time& elapsedTime)
{
	if (m_CurrentSize != m_Transform->size)
	{
		CreateFixture();
	}
	return Component::Update(elapsedTime);
}

void SFENG::BoxCollider::FixedUpdate(const sf::Time& elapsedTime)
{
	return Component::FixedUpdate(elapsedTime);
}

void SFENG::BoxCollider::HandleEvents(sf::Event& event)
{
	return Component::HandleEvents(event);
}

void SFENG::BoxCollider::Print()
{
	std::cout << "BoxCollider Component\n";
	std::cout << "Friction: " << m_Friction << '\n';
	std::cout << "Density: " << m_Density << '\n';
	std::cout << "Sensor: " << ((m_IsSensor) ? "YES" : "NO") << '\n';
}

void SFENG::BoxCollider::CreateFixture()
{
	if (m_Fixture != nullptr)
	{
		m_Body->DestroyFixture(m_Fixture);
	}

	b2PolygonShape polyShape;
	m_CurrentSize = m_Transform->size;
	polyShape.SetAsBox(m_Transform->size.x, m_Transform->size.y);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &polyShape;
	fixtureDef.density = m_Density;
	fixtureDef.friction = m_Friction;
	fixtureDef.isSensor = m_IsSensor;
	m_Fixture = m_Body->CreateFixture(&fixtureDef);
}