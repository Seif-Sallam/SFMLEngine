#pragma once
#include "PCH.h"

class ExplosionController : public SFENG::Component
{
public:
    ExplosionController();
    ~ExplosionController();

    bool Init() override;
    void Update(const sf::Time &elapsed) override;

private:
    sf::Time totalTime;
};