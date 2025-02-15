#include "Components/AsteroidController.h"
#include "Prefabs/Bullet.h"
AstroidController::AstroidController(const Vec2f &position, bool big, const Vec2f &direction)
    : m_Position(position), m_Big(big), m_Direction(direction), alive(true)
{
    if (big)
        speed = 1.0f;
    else
        speed = 1.0f;
    m_Angle = (float)m_Direction.Length();
}

AstroidController::~AstroidController()
{
}

bool AstroidController::Init()
{
    m_Transform = &this->entity->GetComponent<SFENG::Transform>();
    if (this->entity->HasComponent<SFENG::CircleCollider>())
        m_CircleCollider = &this->entity->GetComponent<SFENG::CircleCollider>();
    else
        m_CircleCollider = nullptr;

    if (this->entity->HasComponent<SFENG::Controller>())
        m_Controller = &this->entity->GetComponent<SFENG::Controller>();
    else
        m_Controller = nullptr;

    return Component::Init();
}

void AstroidController::Update(const sf::Time &elapsed)
{
    totalTime += elapsed;
    if (alive && m_Controller)
    {
        auto toRadian = [](float angle)
        { return angle * M_PI_180; };

        m_Controller->Move(speed * m_Direction.x, speed * m_Direction.y);
        Vec2u screenSize = SFENG::Engine::GetWindow().getSize();

        if (m_Transform->position.x < 0.f)
        {
            m_Angle += rand() % 90;
            m_Direction = Vec2f((float)cos(toRadian(m_Angle)), (float)sin(toRadian(m_Angle)));
            m_Controller->SetPosition((float)screenSize.x, m_Transform->position.y);
        }
        else if (m_Transform->position.x > screenSize.x)
        {
            m_Angle += rand() % 90;
            m_Direction = Vec2f((float)cos(toRadian(m_Angle)), (float)sin(toRadian(m_Angle)));
            m_Controller->SetPosition(0.f, m_Transform->position.y);
        }
        if (m_Transform->position.y < 0.f)
        {
            m_Angle += rand() % 90;
            m_Direction = Vec2f((float)cos(toRadian(m_Angle)), (float)sin(toRadian(m_Angle)));
            m_Controller->SetPosition(m_Transform->position.x, (float)screenSize.y);
        }
        else if (m_Transform->position.y > screenSize.y)
        {
            m_Angle += rand() % 90;
            m_Direction = Vec2f((float)cos(toRadian(m_Angle)), (float)sin(toRadian(m_Angle)));
            m_Controller->SetPosition(m_Transform->position.x, 0.f);
        }
    }

    return Component::Update(elapsed);
}

void AstroidController::FixedUpdate(const sf::Time &)
{
    if (m_CircleCollider)
    {
        std::list<SFENG::Entity *> collidingItems = m_CircleCollider->GetCollidingItems();
        for (auto &item : collidingItems)
        {
            bool isBullet = (item->GetTag() == "Bullet");
            if (isBullet)
            {
                alive = false;
            }
        }
    }
}

void AstroidController::SetController(SFENG::Controller *controller)
{
    m_Controller = controller;
}