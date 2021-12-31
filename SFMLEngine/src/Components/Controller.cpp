#include "../../headers/Components/Controller.h"
#include "../../headers/Components/Transform.h"
#include "../../headers/Components/RigidBody2D.h"
#include "../../headers/Components/CircleCollider.h"
#include "../../headers/Components/BoxCollider.h"
#include "../../headers/Entity.h"

namespace SFENG
{
	Controller::Controller()
		: m_Transform(nullptr), m_RigidBody2D(nullptr), speed(0.f)
	{
	}

	Controller::~Controller()
	{
	}

	void Controller::SetRotation(float r)
	{
		m_Transform->angle = r;
		if (m_RigidBody2D)
			m_RigidBody2D->m_Body->SetTransform(m_RigidBody2D->m_Body->GetPosition(), m_Transform->angle);
		if (m_CircleCollider)
			m_CircleCollider->m_Body->SetTransform(m_CircleCollider->m_Body->GetPosition(), m_Transform->angle);
		if (m_BoxCollider)
			m_BoxCollider->m_Body->SetTransform(m_BoxCollider->m_Body->GetPosition(), m_Transform->angle);
	}

	void Controller::Rotate(float r)
	{
		m_Transform->angle += r;
		if (m_RigidBody2D)
			m_RigidBody2D->m_Body->SetTransform(m_RigidBody2D->m_Body->GetPosition(), m_Transform->angle);
		if (m_CircleCollider)
			m_CircleCollider->m_Body->SetTransform(m_CircleCollider->m_Body->GetPosition(), m_Transform->angle);
		if (m_BoxCollider)
			m_BoxCollider->m_Body->SetTransform(m_BoxCollider->m_Body->GetPosition(), m_Transform->angle);
	}

	void Controller::Scale(const Vec2f &factor)
	{
		m_Transform->size.x *= factor.x;
		m_Transform->size.y *= factor.y;
	}

	void Controller::Scale(float xFactor, float yFactor)
	{
		m_Transform->size.x *= xFactor;
		m_Transform->size.y *= yFactor;
	}

	void Controller::Scale(float factor)
	{
		m_Transform->size *= factor;
	}

	void Controller::Resize(float w, float h)
	{
		m_Transform->size = {w, h};
	}

	void Controller::Resize(const Vec2f &v)
	{
		m_Transform->size = v;
	}

	void Controller::Move(const Vec2f &v)
	{
		m_Transform->position += v;
		if (m_RigidBody2D)
		{
			m_RigidBody2D->m_Body->SetTransform(m_Transform->position, m_Transform->angle);
		}
		if (m_CircleCollider)
		{
			m_CircleCollider->m_Body->SetTransform(m_Transform->position, m_Transform->angle);
		}
		if (m_BoxCollider)
		{
			m_BoxCollider->m_Body->SetTransform(m_Transform->position, m_Transform->angle);
		}
	}

	void Controller::Move(float x, float y)
	{
		m_Transform->position += {x, y};
		if (m_RigidBody2D)
		{
			m_RigidBody2D->m_Body->SetTransform(m_Transform->position, m_Transform->angle);
		}
		if (m_CircleCollider)
		{
			m_CircleCollider->m_Body->SetTransform(m_Transform->position, m_Transform->angle);
		}
		if (m_BoxCollider)
		{
			m_BoxCollider->m_Body->SetTransform(m_Transform->position, m_Transform->angle);
		}
	}

	void Controller::SetPosition(const Vec2f &pos)
	{
		m_Transform->position = pos;
		if (m_RigidBody2D)
		{
			m_RigidBody2D->m_Body->SetTransform(m_Transform->position, m_Transform->angle);
		}
		if (m_CircleCollider)
		{
			m_CircleCollider->m_Body->SetTransform(m_Transform->position, m_Transform->angle);
		}
		if (m_BoxCollider)
		{
			m_BoxCollider->m_Body->SetTransform(m_Transform->position, m_Transform->angle);
		}
	}

	void Controller::SetPosition(float x, float y)
	{
		m_Transform->position = {x, y};
		if (m_RigidBody2D)
		{
			m_RigidBody2D->m_Body->SetTransform(m_Transform->position, m_Transform->angle);
		}
		if (m_CircleCollider)
		{
			m_CircleCollider->m_Body->SetTransform(m_Transform->position, m_Transform->angle);
		}
		if (m_BoxCollider)
		{
			m_BoxCollider->m_Body->SetTransform(m_Transform->position, m_Transform->angle);
		}
	}

	bool Controller::Init()
	{
		m_Transform = &this->entity->GetComponent<Transform>();
		if (this->entity->HasComponent<RigidBody2D>())
			m_RigidBody2D = &this->entity->GetComponent<RigidBody2D>();
		else
			m_RigidBody2D = nullptr;

		if (this->entity->HasComponent<BoxCollider>())
			m_BoxCollider = &this->entity->GetComponent<BoxCollider>();
		else
			m_BoxCollider = nullptr;

		if (this->entity->HasComponent<CircleCollider>())
			m_CircleCollider = &this->entity->GetComponent<CircleCollider>();
		else
			m_CircleCollider = nullptr;

		return Component::Init();
	}

	void Controller::Draw(sf::RenderWindow &window)
	{
		return Component::Draw(window);
	}

	void Controller::Update(const sf::Time &elapsedTime)
	{
		return Component::Update(elapsedTime);
	}

	void Controller::FixedUpdate(const sf::Time &elapsedTime)
	{
		return Component::FixedUpdate(elapsedTime);
	}

	void Controller::HandleEvents(sf::Event &event)
	{
		return Component::HandleEvents(event);
	}

	void Controller::Print()
	{
		std::cout << "Controller Component\n";
		std::cout << "Speed: " << speed << '\n';
	}

	void Controller::SetRigidBody(RigidBody2D *rigidBody)
	{
		m_RigidBody2D = rigidBody;
	}

	void Controller::SetBoxCollider(BoxCollider *boxCollider)
	{
		m_BoxCollider = boxCollider;
	}

	void Controller::SetCircleCollider(CircleCollider *circleCollider)
	{
		m_CircleCollider = circleCollider;
	}

}