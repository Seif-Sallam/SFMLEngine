#include "../headers/Prefabs/Explosion.h"
#include "../headers/Components/ExplosionController.h"

Explosion::Explosion(SFENG::Entity *createdEntity, const Vec2f &position)
{
    this->entity = createdEntity;
    SFENG::Transform &transform = entity->GetComponent<SFENG::Transform>();
    transform.position = position;
    SFENG::SpriteRenderer &sp = entity->AddComponent<SFENG::SpriteRenderer>();
    sp.AttachTexture("Explosion");
    SFENG::Animator &animator = entity->AddComponent<SFENG::Animator>();
    {
        SFENG::Animation *animation = animator.AddAnimation("Default");
        animator.SetActiveAnimation("Default");
        for (int i = 0; i < 47; i++)
            animation->AddFrame(sf::IntRect(i * 256, 0, 256, 256), sf::seconds(0.015f));
    }
    sp.SetRect(sf::IntRect(0, 0, 256, 256));
    entity->AddComponent<ExplosionController>();
}