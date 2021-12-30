#include "../headers/Components/ExplosionController.h"

ExplosionController::ExplosionController()
{
}

ExplosionController::~ExplosionController()
{
}

bool ExplosionController::Init()
{
    return Component::Init();
}

void ExplosionController::Update(const sf::Time &elapsed)
{
    totalTime += elapsed;
    if (totalTime > sf::seconds(0.015f * 47))
    {
        this->entity->Destory();
    }
    return Component::Update(elapsed);
}
