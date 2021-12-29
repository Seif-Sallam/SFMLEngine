#include "../headers/Prefabs/Bullet.h"

Bullet::Bullet(SFENG::Entity *createdEntity, const Vec2f &position, const Vec2f &direction)
{
    entity = createdEntity;
    SFENG::Transform &transform = this->entity->GetComponent<SFENG::Transform>();
    transform.position = position;
    transform.size = Vec2f(32.0f, 64.0f);
    SFENG::BoxCollider &collider = this->entity->AddComponent<SFENG::BoxCollider>();
    SFENG::SpriteRenderer &sp = this->entity->AddComponent<SFENG::SpriteRenderer>();
    sp.AttachTexture("Bullet");
    SFENG::Animator &animator = this->entity->AddComponent<SFENG::Animator>();
    {
        SFENG::Animation *animation = animator.AddAnimation("Fire");
        animator.SetActiveAnimation("Fire");
        animation->Loop(true);
        for (int i = 0; i < 16; i++)
            animation->AddFrame(sf::IntRect(i * 32, 0, 32, 64), sf::seconds(0.1f));
    }
    sp.SetRect(sf::IntRect(0, 0, 32, 64));
    m_bController = &this->entity->AddComponent<BulletController>(position, direction);
    sp.SetScale(0.7f, 0.7f);
}

bool Bullet::IsAlive()
{
    return m_bController->alive;
}