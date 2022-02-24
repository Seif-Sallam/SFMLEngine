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
    if (this->entity->HasComponent<SFENG::Controller>())
    {
        this->SetController(&this->entity->GetComponent<SFENG::Controller>());
    }
    else
        m_Controller = nullptr;
    if (this->entity->HasComponent<SFENG::BoxCollider>())
    {
        m_BoxCollider = &this->entity->GetComponent<SFENG::BoxCollider>();
    }
    else
    {
        m_BoxCollider = nullptr;
    }
    return SFENG::Component::Init();
}

void BulletController::Update(const sf::Time &elapsed)
{
    if (alive && m_Controller)
    {
        m_Controller->Move(Vec2f(speed * elapsed.asSeconds() * m_Direction));
        Vec2u screenSize = SFENG::Engine::GetWindow().getSize();
        if (m_Transform->position.x < 0.f || m_Transform->position.y < 0.f || m_Transform->position.x > screenSize.x ||
            m_Transform->position.y > screenSize.y)
            alive = false;
    }
}

void BulletController::SetController(SFENG::Controller *controller)
{
    m_Controller = controller;
    m_Controller->SetPosition(m_Position);
    m_Controller->SetRotation(atan2f(m_Direction.y, m_Direction.x) * M_180_PI + 90.0f);
}

void BulletController::FixedUpdate(const sf::Time &)
{
    if (this->m_BoxCollider)
    {
        std::list<SFENG::Entity *> collidingItems = m_BoxCollider->GetCollidingItems();
        for (auto &item : collidingItems)
        {
            bool isAstroid = (item->GetTag() == "Astroid");
            if (isAstroid)
            {
                alive = false;
            }
        }
    }
}