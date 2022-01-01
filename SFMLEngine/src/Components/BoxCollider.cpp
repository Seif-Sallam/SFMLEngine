#include "Components/BoxCollider.h"
#include "Components/CircleCollider.h"
#include "Components/RigidBody2D.h"
#include "Entity.h"
#include "Engine.h"

namespace SFENG
{

	BoxCollider::BoxCollider()
		: m_PhysWorld(&Engine::GetPhysicsWorld()), m_Body(nullptr), m_Fixture(nullptr), m_Transform(nullptr), m_CurrentSize(Vec2f(0.0f, 0.0f)), m_Friction(0.3f), m_Density(1.0f), m_IsSensor(false)
	{
	}

	BoxCollider::~BoxCollider()
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

	void BoxCollider::SetFriction(float f)
	{
		m_Fixture->SetFriction(f);
		m_Friction = f;
	}

	void BoxCollider::SetDensity(float d)
	{
		m_Fixture->SetDensity(d);
		m_Density = d;
	}

	b2Body *BoxCollider::GetBody()
	{
		return m_Body;
	}

	b2Shape *BoxCollider::GetShape()
	{
		return m_Fixture->GetShape();
	}

	void BoxCollider::SetSensor(bool s)
	{
		m_IsSensor = s;
		m_Fixture->SetSensor(s);
	}

	bool BoxCollider::Init()
	{
		m_Transform = &this->entity->GetComponent<Transform>();
		if (this->entity->HasComponent<CircleCollider>())
		{
			std::cout << "Cannot add Circle Collider and Box COllider to the same entity\n";
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
			bodyDef.position = m_Transform->position;
			bodyDef.angle = m_Transform->angle / 180.f * M_PI;
			bodyDef.type = b2BodyType::b2_staticBody;
			b2BodyUserData data;
			data.pointer = reinterpret_cast<uintptr_t>(entity);
			bodyDef.userData = data;
			m_Body = m_PhysWorld->CreateBody(&bodyDef);
		}
		CreateFixture();
		return Component::Init();
	}

	void BoxCollider::Draw(sf::RenderWindow &window)
	{
		return Component::Draw(window);
	}

	void BoxCollider::Update(const sf::Time &elapsedTime)
	{
		if (m_CurrentSize != m_Transform->size)
		{
			if (this->entity->IsAlive())
				CreateFixture();
		}
		return Component::Update(elapsedTime);
	}

	void BoxCollider::FixedUpdate(const sf::Time &elapsedTime)
	{
		return Component::FixedUpdate(elapsedTime);
	}

	void BoxCollider::HandleEvents(sf::Event &event)
	{
		return Component::HandleEvents(event);
	}

	void BoxCollider::Print()
	{
		std::cout << "BoxCollider Component\n";
		std::cout << "Friction: " << m_Friction << '\n';
		std::cout << "Density: " << m_Density << '\n';
		std::cout << "Sensor: " << ((m_IsSensor) ? "YES" : "NO") << '\n';
	}

	void BoxCollider::CreateFixture()
	{
		if (m_Fixture != nullptr)
		{
			if (m_Fixture->GetBody() == m_Body)
			{
				m_Body->DestroyFixture(m_Fixture);
			}
		}

		b2PolygonShape polyShape;
		m_CurrentSize = m_Transform->size;
		polyShape.SetAsBox(m_Transform->size.x / 2.0f, m_Transform->size.y / 2.0f);
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &polyShape;
		fixtureDef.density = m_Density;
		fixtureDef.friction = m_Friction;
		fixtureDef.isSensor = m_IsSensor;
		m_Fixture = m_Body->CreateFixture(&fixtureDef);
	}

	std::list<Entity *> BoxCollider::GetCollidingItems()
	{
		const std::list<std::pair<Entity *, Entity *>> &contactItems = Engine::GetContactList();
		std::list<Entity *> collidingItems;

		for (auto item : contactItems)
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