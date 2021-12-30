#pragma once
#include "PCH.h"
class Astroid;
class AstroidsCreator : public SFENG::Component
{
public:
    AstroidsCreator();
    ~AstroidsCreator();

    bool Init() override;
    void Update(const sf::Time &elapsed) override;

private:
    void HandleDeadAstroids();

    int32_t m_AstroidsCount;
    sf::Time m_PassedTime;
    sf::Time m_RateOfSpawn;
    std::mt19937 m_RandomGenerator;
    std::vector<std::unique_ptr<Astroid>> m_Astroids;
};