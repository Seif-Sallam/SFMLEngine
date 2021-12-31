#include "../headers/Prefabs/Astroid.h"
#include "../headers/Components/AstroidController.h"
Astroid::Astroid(SFENG::Entity *createdEntity, const Vec2f &position, const Vec2f &direction, bool big)
{
    entity = createdEntity;
    entity->SetTag("Astroid");
    SFENG::Transform &transform = this->entity->AddComponent<SFENG::Transform>();
    SFENG::SpriteRenderer &sp = this->entity->AddComponent<SFENG::SpriteRenderer>();
    SFENG::Animator &animator = this->entity->AddComponent<SFENG::Animator>();
    if (big)
    {
        transform.size.x = 800.0f;
        sp.AttachTexture("BIG_Astroid");
    }
    else
    {
        transform.size.x = 600.0f;
        sp.AttachTexture("SMALL_Astroid");
    }
    SFENG::CircleCollider &cc = this->entity->AddComponent<SFENG::CircleCollider>();
    sp.SetRect(sf::IntRect(0, 0, 64, 64));
    {
        SFENG::Animation *animation = animator.AddAnimation("Move");
        animation->Loop(true);
        animator.SetActiveAnimation("Move");
        for (int i = 0; i < 15; i++)
            animation->AddFrame(sf::IntRect(0, 0, 64, 64), sf::seconds(0.1f));
    }

    m_Controller = &this->entity->AddComponent<AstroidController>(position, big, direction);
    SFENG::RigidBody2D *rb = &this->entity->AddComponent<SFENG::RigidBody2D>();
    rb->SetBodyType(b2BodyType::b2_dynamicBody);
}

bool Astroid::IsAlive()
{
    return m_Controller->alive;
}