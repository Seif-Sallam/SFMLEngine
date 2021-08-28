#include "../../headers/Components/CircleCollider.h"
#include "../../headers/Components/RigidBody2D.h"
#include "../../headers/Entity.h"

SFENG::CircleCollider::CircleCollider(b2World* world)
	: m_PhysWorld(world)
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

inline void SFENG::CircleCollider::SetFriction(float f)
{
	m_Fixture->SetFriction(f);
	m_Friction = f;
}

inline void SFENG::CircleCollider::SetDensity(float d)
{
	m_Fixture->SetDensity(d);
	m_Density = d;
}

inline b2Body* SFENG::CircleCollider::GetBody()
{
	return m_Body;
}

inline b2Shape* SFENG::CircleCollider::GetShape()
{
	return m_Fixture->GetShape();
}

inline void SFENG::CircleCollider::SetSensor(bool s)
{
	m_IsSensor = s;
	m_Fixture->SetSensor(s);
}

inline bool SFENG::CircleCollider::Init()
{
	m_Transform = &this->entity->GetCopmonent<Transform>();
	if (this->entity->HasComponent<RigidBody2D>()) {
		RigidBody2D& rb = entity->GetCopmonent<RigidBody2D>();
		m_Body = rb.GetBody();
	}
	else
	{
		b2BodyDef bodyDef;
		bodyDef.position = m_Transform->position;
		bodyDef.angle = m_Transform->rotation;
		bodyDef.type = b2BodyType::b2_staticBody;
		m_Body = m_PhysWorld->CreateBody(&bodyDef);
	}
	CreateFixture();
	
	return Component::Init();
}

inline void SFENG::CircleCollider::Draw(sf::RenderWindow& window)
{
	return Component::Draw(window);
}

inline void SFENG::CircleCollider::Update(const sf::Time& elapsedTime)
{
	if (m_Radius != m_Transform->size.x)
	{
		CreateFixture();
	}
	return Component::Update(elapsedTime);
}

inline void SFENG::CircleCollider::FixedUpdate(const sf::Time& elapsedTime)
{
	return Component::FixedUpdate(elapsedTime);
}

inline void SFENG::CircleCollider::HandleEvents(sf::Event& event)
{
	return Component::HandleEvents(event);
}

inline void SFENG::CircleCollider::Print()
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
	shape.m_radius = m_Radius;
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.density = m_Density;
	fixtureDef.friction = m_Friction;
	fixtureDef.isSensor = m_IsSensor;
	m_Fixture = m_Body->CreateFixture(&fixtureDef);
}