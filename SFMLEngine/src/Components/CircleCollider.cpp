#include "Components/CircleCollider.h"
#include "Components/RigidBody2D.h"
#include "Components/BoxCollider.h"
#include "Entity.h"
#include "Engine.h"
#define _USE_MATH_DEFINES
#include <math.h>

namespace SFENG
{

	CircleCollider::CircleCollider()
		: m_PhysWorld(&Engine::GetPhysicsWorld()), m_Body(nullptr), m_Fixture(nullptr), m_Transform(nullptr), m_Radius(0.0f), m_Friction(0.3f), m_Density(1.0f), m_IsSensor(false)
	{
	}

	CircleCollider::~CircleCollider()
	{
		if (m_Fixture != nullptr && m_Body != nullptr)
		{
			m_Body->DestroyFixture(m_Fixture);
			m_PhysWorld->DestroyBody(m_Body);
		}

		if (this->entity->HasComponent<RigidBody2D>())
		{
			auto rb = &this->entity->GetComponent<RigidBody2D>();
			if (rb != nullptr)
				rb->m_Body = nullptr;
		}
	}

	void CircleCollider::SetFriction(float f)
	{
		m_Fixture->SetFriction(f);
		m_Friction = f;
	}

	void CircleCollider::SetDensity(float d)
	{
		m_Fixture->SetDensity(d);
		m_Density = d;
	}

	b2Body *CircleCollider::GetBody()
	{
		return m_Body;
	}

	b2Shape *CircleCollider::GetShape()
	{
		return m_Fixture->GetShape();
	}

	void CircleCollider::SetSensor(bool s)
	{
		m_IsSensor = s;
		m_Fixture->SetSensor(s);
	}

	bool CircleCollider::Init()
	{
		m_Transform = &this->entity->GetComponent<Transform>();
		if (this->entity->HasComponent<BoxCollider>())
		{
			std::cout << "You cannot have both Box collider and Circle Collider\n";
			return false;
		}
		if (this->entity->HasComponent<RigidBody2D>())
		{
			RigidBody2D &rb = entity->GetComponent<RigidBody2D>();
			m_Body = rb.m_Body;
		}
		else
		{
			b2BodyDef bodyDef;
			bodyDef.position = m_Transform->position / Engine::GetPPM();
			bodyDef.angle = m_Transform->angle / 180.0f * M_PI;
			bodyDef.type = b2BodyType::b2_staticBody;
			b2BodyUserData data;
			data.pointer = reinterpret_cast<uintptr_t>(entity);
			bodyDef.userData = data;
			m_Body = m_PhysWorld->CreateBody(&bodyDef);
		}
		CreateFixture();

		return Component::Init();
	}

	void CircleCollider::Draw(sf::RenderWindow &window)
	{
		return Component::Draw(window);
	}

	void CircleCollider::Update(const sf::Time &elapsedTime)
	{
		if (m_Radius != m_Transform->size.x / Engine::GetPPM())
		{
			CreateFixture();
		}
		return Component::Update(elapsedTime);
	}

	void CircleCollider::FixedUpdate(const sf::Time &elapsedTime)
	{
		return Component::FixedUpdate(elapsedTime);
	}

	void CircleCollider::HandleEvents(sf::Event &event)
	{
		return Component::HandleEvents(event);
	}

	void CircleCollider::Print()
	{
		std::cout << "CircleCollider Component\n";
		std::cout << "Friction: " << m_Friction << '\n';
		std::cout << "Density: " << m_Density << '\n';
		std::cout << "Sensor: " << ((m_IsSensor) ? "YES" : "NO") << '\n';
	}

	void CircleCollider::CreateFixture()
	{
		if (m_Fixture != nullptr)
		{
			if (m_Fixture->GetBody() == m_Body)
			{
				m_Body->DestroyFixture(m_Fixture);
			}
		}
		b2CircleShape shape;
		m_Radius = m_Transform->size.x / Engine::GetPPM();
		shape.m_radius = m_Radius;
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &shape;
		fixtureDef.density = m_Density;
		fixtureDef.friction = m_Friction;
		fixtureDef.isSensor = m_IsSensor;
		m_Fixture = m_Body->CreateFixture(&fixtureDef);
	}

	std::list<Entity *> CircleCollider::GetCollidingItems()
	{
		const std::list<std::pair<Entity *, Entity *>> &contactItems = Engine::GetContactList();
		std::list<Entity *> collidingItems;
		for (auto &item : contactItems)
		{
			if (item.first->GetName() == this->entity->GetName())
			{
				collidingItems.push_back(item.second);
			}
			else if (item.second->GetName() == this->entity->GetName())
			{
				collidingItems.push_back(item.first);
			}
		}
		return collidingItems;
	}
}