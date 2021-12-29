#include "../headers/Prefabs/SpaceShip.h"
#include "../headers/Components/PlayerController.h"
SpaceShip::SpaceShip(SFENG::Entity *createdEntity)
    : entity(createdEntity)
{
    SFENG::Controller &controller = entity->AddComponent<SFENG::Controller>();
    SFENG::Transform &transform = entity->GetComponent<SFENG::Transform>();
    SFENG::SpriteRenderer &spriteRenderer = entity->AddComponent<SFENG::SpriteRenderer>();
    SFENG::BoxCollider &boxCollider = entity->AddComponent<SFENG::BoxCollider>();
    SFENG::ResourceManager::AddTexture("rsc/textures/spaceship.png", "SpaceShip");
    spriteRenderer.AttachTexture("SpaceShip");
    m_Animator = &entity->AddComponent<SFENG::Animator>();
    m_Animator->AttachSpriteRenderer(&spriteRenderer);
    SetAnimations();
    SetPlayerController();
}

void SpaceShip::SetAnimations()
{
    {
        auto leftAnimationNT = m_Animator->AddAnimation("NT_LEFT");
        leftAnimationNT->AddFrame(sf::IntRect(86, 0, 36, 40), sf::seconds(0.2f));
        leftAnimationNT->Loop(true);
    }
    {
        auto leftAnimation = m_Animator->AddAnimation("LEFT");
        leftAnimation->AddFrame(sf::IntRect(86, 40, 40, 43), sf::seconds(0.2f));
        leftAnimation->AddFrame(sf::IntRect(86, 86, 40, 43), sf::seconds(0.2f));
        leftAnimation->Loop(true);
    }
    {
        auto rightAnimationNT = m_Animator->AddAnimation("NT_RIGHT");
        rightAnimationNT->AddFrame(sf::IntRect(0, 0, 38, 40), sf::seconds(0.2f));
        rightAnimationNT->Loop(true);
    }
    {
        auto rightAnimation = m_Animator->AddAnimation("RIGHT");
        rightAnimation->AddFrame(sf::IntRect(0, 40, 38, 43), sf::seconds(0.2f));
        rightAnimation->AddFrame(sf::IntRect(0, 86, 38, 43), sf::seconds(0.2f));
        rightAnimation->Loop(true);
    }
    {
        auto frontAnimationNT = m_Animator->AddAnimation("NT_FRONT");
        frontAnimationNT->AddFrame(sf::IntRect(39, 0, 40, 40), sf::seconds(0.2f));
        frontAnimationNT->Loop(true);
    }
    {
        auto frontAnimation = m_Animator->AddAnimation("FRONT");
        frontAnimation->AddFrame(sf::IntRect(39, 40, 38, 43), sf::seconds(0.1f));
        frontAnimation->AddFrame(sf::IntRect(39, 86, 38, 43), sf::seconds(0.1f));
        frontAnimation->Loop(true);
    }
}
void SpaceShip::SetPlayerController()
{
    PlayerController &playerController = this->entity->AddComponent<PlayerController>();
    SFENG::Controller &controller = this->entity->GetComponent<SFENG::Controller>();
}
