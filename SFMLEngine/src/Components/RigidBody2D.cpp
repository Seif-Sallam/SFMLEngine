#include "../../headers/Components/RigidBody2D.h"
#include "../../headers/Components/BoxCollider.h"
#include "../../headers/Components/Transform.h"
#include "../../headers/Components/CircleCollider.h"
#include "../../headers/Entity.h"

SFENG::RigidBody2D::RigidBody2D(b2World* world)
	: m_PhysWorld(world)
	, m_Body(nullptr)
	, m_Transform(nullptr)
{
}

SFENG::RigidBody2D::~RigidBody2D()
{
	m_PhysWorld->DestroyBody(m_Body);
	m_Body = nullptr;
}

void SFENG::RigidBody2D::SetBodyType(const b2BodyType& type)
{
	if (m_Body != nullptr)
	{
		m_Body->SetType(type);
	}
}

Vec2f SFENG::RigidBody2D::GetPosition()
{
	if (m_Body != nullptr)
		return m_Body->GetPosition();
	else
		return Vec2f();
}

void SFENG::RigidBody2D::SetPosition(const Vec2f& v)
{
	m_Transform->position = v;
	m_Body->SetTransform(m_Transform->position, m_Transform->angle);
}

float SFENG::RigidBody2D::GetAngle()
{
	if (m_Body != nullptr)
		return m_Body->GetAngle();
	else
		return 0.f;
}

b2Body* SFENG::RigidBody2D::GetBody()
{
	return m_Body;
}

b2Fixture* SFENG::RigidBody2D::CreateFixture(const b2Shape* shape, float dinsety)
{
	if (m_Body != nullptr)
		return m_Body->CreateFixture(shape, dinsety);
	else
		return nullptr;
}

b2Fixture* SFENG::RigidBody2D::CreateFixture(const b2FixtureDef* def)
{
	if (m_Body != nullptr)
		return m_Body->CreateFixture(def);
	else
		return nullptr;
}

bool SFENG::RigidBody2D::Init()
{
	if (m_PhysWorld != nullptr)
	{
		m_Transform = &this->entity->GetCopmonent<Transform>();
		if (this->entity->HasComponent<CircleCollider>())
		{
			m_Body = this->entity->GetCopmonent<CircleCollider>().m_Body;
		}
		else if (this->entity->HasComponent<BoxCollider>())
		{
			m_Body = this->entity->GetCopmonent<BoxCollider>().m_Body;
		}
		else
		{
			b2BodyDef bodyDef;
			bodyDef.position.Set(m_Transform->position.x, m_Transform->position.y);
			bodyDef.angle = m_Transform->angle;
			bodyDef.type = b2BodyType::b2_staticBody;
			m_Body = this->m_PhysWorld->CreateBody(&bodyDef);
		}
	}
	else
		return false;
	return Component::Init();
}

void SFENG::RigidBody2D::Draw(sf::RenderWindow& window)
{
	return Component::Draw(window);
}

void SFENG::RigidBody2D::Update(const sf::Time& elapsedTime)
{
	//m_Body->SetTransform(m_Transform->position, m_Transform->rotation);
	return Component::Update(elapsedTime);
}

void SFENG::RigidBody2D::FixedUpdate(const sf::Time& elapsedTime)
{
	if (m_Body != nullptr)
	{
		m_Transform->position = m_Body->GetPosition();
		m_Transform->angle = m_Body->GetAngle();
	}
	return Component::FixedUpdate(elapsedTime);
}

void SFENG::RigidBody2D::HandleEvents(sf::Event& event)
{
	return Component::HandleEvents(event);
}

void SFENG::RigidBody2D::Print()
{
	const std::string typeNames[] = { "Static", "Kinematic", "Dynamic", "" };
	std::cout << "RigidBody2D Component\n";
	if (m_Body != nullptr)
	{
		std::cout << "Type: " << typeNames[(uint32_t)(m_Body->GetType())] << '\n';
		std::cout << "Mass: " << m_Body->GetMass() << '\n';
	}
	else
	{
		std::cout << "Body = nullptr\n";
	}
}