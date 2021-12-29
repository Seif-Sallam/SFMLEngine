#include "../headers/Components/PlayerController.h"
#include "../headers/Prefabs/Bullet.h"
PlayerController::PlayerController()
    : m_CurrentDirection(FRONT), m_Thrusting(false), m_Alive(true), m_RotationSpeed(300.f), m_Angle(0.f), m_MaxSpeed(350.f),
      m_BulletsShotCount(0), m_AliveBullets(0), m_TotalElapsedTime(sf::seconds(0.f)), m_BulletFireRate(0.1f),
      m_BulletNextShot(0.2f)
{

    m_Velocity.One();
}

bool PlayerController::Init()
{
    if (this->entity->HasComponent<SFENG::Controller>())
        this->m_Controller = &this->entity->GetComponent<SFENG::Controller>();
    else
        this->m_Controller = nullptr;

    if (this->entity->HasComponent<SFENG::Animator>())
        this->m_Animator = &this->entity->GetComponent<SFENG::Animator>();
    else
        this->m_Animator = nullptr;

    m_Transform = &this->entity->GetComponent<SFENG::Transform>();
    return SFENG::Component::Init();
}

void PlayerController::Update(const sf::Time &elapsed)
{
    if (m_Controller)
        HandleControls(elapsed);
    if (m_Animator)
        HandleAnimations(elapsed);

    HandleBullets();
}

void PlayerController::FixedUpdate(const sf::Time &elapsed)
{
    // Handle Collisions
    /*
        Handling Bullet hitting an Astroid is in the Astroid itself since it is the one that will be deactivated
        Handling the collision between the Player and the Astroid happens here
        @TODO: Handle The collision with the Astroid
    */
}

void PlayerController::SetController(SFENG::Controller *c)
{
    m_Controller = c;
}

void PlayerController::SetAnimator(SFENG::Animator *animator)
{
    m_Animator = animator;
}

void PlayerController::HandleAnimations(const sf::Time &elapsed)
{
    switch (m_CurrentDirection)
    {
    case FRONT:
    {
        if (m_Thrusting)
            m_Animator->SetActiveAnimation("FRONT");
        else
            m_Animator->SetActiveAnimation("NT_FRONT");
    }
    break;
    case RIGHT:
    {
        if (m_Thrusting)
            m_Animator->SetActiveAnimation("RIGHT");
        else
            m_Animator->SetActiveAnimation("NT_RIGHT");
    }
    break;
    case LEFT:
    {
        if (m_Thrusting)
            m_Animator->SetActiveAnimation("LEFT");
        else
            m_Animator->SetActiveAnimation("NT_LEFT");
    }
    break;
    }
}

void PlayerController::HandleControls(const sf::Time &elapsed)
{
    if (m_Alive)
    {
        m_TotalElapsedTime += elapsed;
        auto toRadian = [](float degree)
        { return degree * M_PI_180; };
        m_CurrentDirection = FRONT;
        if (SFENG::Keyboard::IsKeyPressed(sf::Keyboard::W))
            m_Thrusting = true;
        else
            m_Thrusting = false;

        if (SFENG::Keyboard::IsKeyPressed(sf::Keyboard::D))
        {
            m_Angle += m_RotationSpeed * elapsed.asSeconds();
            m_CurrentDirection = RIGHT;
        }
        if (SFENG::Keyboard::IsKeyPressed(sf::Keyboard::A))
        {
            m_Angle -= m_RotationSpeed * elapsed.asSeconds();
            m_CurrentDirection = LEFT;
        }

        Vec2f dir = Vec2f(cos(toRadian(m_Angle)), sin(toRadian(m_Angle)));
        // float distance = dir.Length();

        // dir /= distance;

        if (m_Thrusting)
        {
            m_Velocity.x += dir.x * 4.0f;
            m_Velocity.y += dir.y * 4.0f;
        }
        else
        {
            m_Velocity.x *= 0.999f;
            m_Velocity.y *= 0.999f;
        }

        float speed = m_Velocity.Length();
        if (speed > m_MaxSpeed)
            m_Velocity *= m_MaxSpeed / speed;

        Vec2f movementDist = m_Velocity * elapsed.asSeconds();

        m_Controller->Move(movementDist);
        Vec2f finalPosition = m_Transform->position;

        Vec2u windowSize = SFENG::Engine::GetWindow().getSize();
        if (finalPosition.x > windowSize.x)
            finalPosition.x = 0.f;
        else if (finalPosition.x < 0.f)
            finalPosition.x = windowSize.x;

        if (finalPosition.y > windowSize.y)
            finalPosition.y = 0.f;
        else if (finalPosition.y < 0.f)
            finalPosition.y = windowSize.y;

        m_Controller->SetPosition(finalPosition);
        m_Controller->SetRotation(m_Angle + 90.f);

        if (SFENG::Keyboard::IsKeyPressed(sf::Keyboard::Space) && m_AliveBullets < 50 && m_TotalElapsedTime.asSeconds() > m_BulletNextShot)
        {
            m_BulletsShotCount++;
            m_BulletNextShot = m_TotalElapsedTime.asSeconds() + m_BulletFireRate;
            AddBullet();
        }
    }
}

void PlayerController::AddBullet()
{
    auto toRadian = [](float angle)
    { return angle * M_PI_180; };
    Vec2f dir = Vec2f(cos(toRadian(m_Angle)), sin(toRadian(m_Angle)));
    SFENG::Entity *bulletEntity = SFENG::LCM::InstantiateObject("Bullet#" + std::to_string(m_BulletsShotCount));
    m_Bullets.push_back(std::make_unique<Bullet>(bulletEntity, this->m_Transform->position, dir));
}

void PlayerController::HandleBullets()
{
    for (int i = 0; i < m_Bullets.size(); i++)
    {
        if (!m_Bullets[i]->IsAlive())
        {
            m_Bullets[i]->entity->Destory();
            // erasing the pointer is just deleting the data inside
            // but the LCM will take care of deleting the components and the entity itself
            m_Bullets.erase(m_Bullets.begin() + i);
            i--;
        }
    }
}