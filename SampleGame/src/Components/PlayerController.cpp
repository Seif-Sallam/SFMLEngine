#include "Components\PlayerController.h"

PlayerController::PlayerController()
	: m_Controller(nullptr)
{
}

bool PlayerController::Init()
{
	if (this->entity->HasComponent<SFENG::Controller>())
		this->m_Controller = &this->entity->GetCopmonent<SFENG::Controller>();
	else
		this->m_Controller = nullptr;
	return SFENG::Component::Init();
}

void PlayerController::Update(const sf::Time& elapsed)
{
	if (m_Controller) {
		if (SFENG::Keyboard::IsKeyPressed(sf::Keyboard::Left))
		{
			this->m_Controller->Move(Vec2f(-speed * elapsed.asSeconds(), 0));
		}
		if (SFENG::Keyboard::IsKeyPressed(sf::Keyboard::Right))
		{
			this->m_Controller->Move(Vec2f(speed * elapsed.asSeconds(), 0));
		}
		if (SFENG::Keyboard::IsKeyPressed(sf::Keyboard::Up))
		{
			this->m_Controller->Move(Vec2f(0, -speed * elapsed.asSeconds()));
		}
		if (SFENG::Keyboard::IsKeyPressed(sf::Keyboard::Down))
		{
			this->m_Controller->Move(Vec2f(0, speed * elapsed.asSeconds()));
		}
	}

}

void PlayerController::FixedUpdate(const sf::Time& elapsed)
{
}

void PlayerController::SetController(SFENG::Controller* c)
{
	m_Controller = c;
}
