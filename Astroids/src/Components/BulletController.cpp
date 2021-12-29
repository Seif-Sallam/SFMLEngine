#include "../headers/Components/BulletController.h"

BulletController::BulletController(const Vec2f &position, const Vec2f &direction)
    : m_Position(position), m_Transform(nullptr), m_Direction(direction), speed(800.f), alive(true)
{
}

BulletController::~BulletController()
{
}

bool BulletController::Init()
{
    m_Transform = &this->entity->GetComponent<SFENG::Transform>();
    m_Transform->position = m_Position;
    m_Transform->angle = atan2f(m_Direction.y, m_Direction.x) * M_180_PI + 90.0f;
    return SFENG::Component::Init();
}

void BulletController::Update(const sf::Time &elapsed)
{
    if (alive)
    {
        m_Transform->position += Vec2f(speed * elapsed.asSeconds() * m_Direction);
        Vec2u screenSize = SFENG::Engine::GetWindow().getSize();
        if (m_Transform->position.x < 0.f || m_Transform->position.y < 0.f || m_Transform->position.x > screenSize.x ||
            m_Transform->position.y > screenSize.y)
            alive = false;
    }
}
