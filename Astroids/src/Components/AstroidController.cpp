#include "../headers/Components/AstroidController.h"

AstroidController::AstroidController(const Vec2f &position, bool big, const Vec2f &direction)
    : m_Position(position), m_Big(big), m_Direction(direction), alive(true)
{
    if (big)
        speed = 5.0f;
    else
        speed = 7.0f;
    m_Angle = m_Direction.Length();
}

AstroidController::~AstroidController()
{
}

bool AstroidController::Init()
{
    m_Transform = &this->entity->GetComponent<SFENG::Transform>();

    return Component::Init();
}

void AstroidController::Update(const sf::Time &elapsed)
{
    totalTime += elapsed;
    if (alive)
    {
        auto toRadian = [](float angle)
        { return angle * M_PI_180; };

        m_Transform->position.x += speed * m_Direction.x;
        m_Transform->position.y += speed * m_Direction.y;
        Vec2u screenSize = SFENG::Engine::GetWindow().getSize();

        if (m_Transform->position.x < 0.f)
        {
            m_Angle += rand() % 90;
            m_Direction = Vec2f(cos(toRadian(m_Angle)), sin(toRadian(m_Angle)));
            m_Transform->position.x = screenSize.x;
        }
        else if (m_Transform->position.x > screenSize.x)
        {
            m_Angle += rand() % 90;
            m_Direction = Vec2f(cos(toRadian(m_Angle)), sin(toRadian(m_Angle)));
            m_Transform->position.x = 0.f;
        }
        if (m_Transform->position.y < 0.f)
        {
            m_Angle += rand() % 90;
            m_Direction = Vec2f(cos(toRadian(m_Angle)), sin(toRadian(m_Angle)));
            m_Transform->position.y = screenSize.y;
        }
        else if (m_Transform->position.y > screenSize.y)
        {
            m_Angle += rand() % 90;
            m_Direction = Vec2f(cos(toRadian(m_Angle)), sin(toRadian(m_Angle)));
            m_Transform->position.y = 0.f;
        }
    }
    if (totalTime > sf::seconds(5.0f))
    {
        alive = false;
    }
    return Component::Update(elapsed);
}
