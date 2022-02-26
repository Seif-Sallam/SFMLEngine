#include "../headers/Prefabs/Astroid.h"
#include "../headers/Components/AstroidController.h"
Astroid::Astroid(SFENG::Entity *createdEntity, const Vec2f &position, const Vec2f &direction, bool big)
{
    entity = createdEntity;
    entity->SetTag("Astroid");
    SFENG::Transform &transform = this->entity->AddComponent<SFENG::Transform>();
    SFENG::SpriteRenderer &sp = this->entity->AddComponent<SFENG::SpriteRenderer>();
    SFENG::Animator &animator = this->entity->AddComponent<SFENG::Animator>();
    SFENG::CircleCollider &cc = this->entity->AddComponent<SFENG::CircleCollider>();
    SFENG::RigidBody2D *rb = &this->entity->AddComponent<SFENG::RigidBody2D>();
    cc.SetSensor(true);
    rb->SetBodyType(b2BodyType::b2_dynamicBody);
    if (big)
    {
        transform.size.x = 10.0f;
        sp.AttachTexture("BIG_Astroid");
    }
    else
    {
        transform.size.x = 5.0f;
        sp.AttachTexture("SMALL_Astroid");
    }

    sp.SetRect(sf::IntRect(0, 0, 64, 64));
    {
        SFENG::Animation *animation = animator.AddAnimation("Move");
        animation->Loop(true);
        animator.SetActiveAnimation("Move");
        for (int i = 0; i < 15; i++)
            animation->AddFrame(sf::IntRect(0, 0, 64, 64), sf::seconds(0.1f));
    }

    m_Controller = &this->entity->AddComponent<AstroidController>(position, big, direction);
}

bool Astroid::IsAlive()
{
    return m_Controller->alive;
}