#pragma once
#include "PCH.h"
class Asteroid;
class AsteroidsCreator : public SFENG::Component
{
public:
    AsteroidsCreator();
    ~AsteroidsCreator();

    bool Init() override;
    void Update(const sf::Time &elapsed) override;

private:
    void HandleDeadAsteroids();

    int32_t m_AsteroidsCount;
    sf::Time m_PassedTime;
    sf::Time m_RateOfSpawn;
    std::mt19937 m_RandomGenerator;
    std::vector<std::unique_ptr<Asteroid>> m_Asteroids;
};