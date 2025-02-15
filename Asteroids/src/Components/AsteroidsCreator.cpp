#include "Components/AsteroidsCreator.h"
#include "Components/AsteroidController.h"
#include "Prefabs/Asteroid.h"
#include "Prefabs/Explosion.h"

AsteroidsCreator::AsteroidsCreator()
    : m_AsteroidsCount(0), m_PassedTime(sf::Time::Zero), m_RateOfSpawn(sf::seconds(1.f))
{
    m_RandomGenerator.seed(time(0));
}

AsteroidsCreator::~AsteroidsCreator()
{
}

bool AsteroidsCreator::Init()
{
    return this->Component::Init();
}

void AsteroidsCreator::Update(const sf::Time &elapsed)
{
    static std::uniform_int_distribution<int> dist(0, 1);
    static std::uniform_real_distribution<float> positionX(100.f, 1300.f);
    static std::uniform_real_distribution<float> positionY(25.f, 800.f);
    static std::uniform_real_distribution<float> direction(-1.f, 1.f);
    m_PassedTime += elapsed;
    if (m_PassedTime >= m_RateOfSpawn && m_Asteroids.size() < 15)
    {
        m_PassedTime = sf::seconds(0.f);
        m_AsteroidsCount++;
        Vec2f position = Vec2f(positionX(m_RandomGenerator), positionY(m_RandomGenerator));
        Vec2f directionVec = Vec2f(direction(m_RandomGenerator), direction(m_RandomGenerator));
        bool big = dist(m_RandomGenerator);
        SFENG::Entity *astroidEntity = SFENG::LCM::InstantiateObject("Asteroid#" + std::to_string(m_AsteroidsCount));
        m_Asteroids.push_back(std::make_unique<Asteroid>(
            astroidEntity, position, directionVec, big));

        auto &controller = astroidEntity->AddComponent<SFENG::Controller>();
        auto &astroidController = astroidEntity->GetComponent<AstroidController>();
        astroidController.SetController(&controller);
    }
    HandleDeadAsteroids();
    return this->Component::Update(elapsed);
}

void AsteroidsCreator::HandleDeadAsteroids()
{
    for (int i = 0; i < m_Asteroids.size(); i++)
    {
        if (!m_Asteroids[i]->IsAlive())
        {
            std::cout << "Deleted\n";
            Vec2f pos = m_Asteroids[i]->entity->GetComponent<SFENG::Transform>().position;
            Explosion e(SFENG::LCM::InstantiateObject("Explosion#" + std::to_string(m_AsteroidsCount - 1)), pos);
            m_Asteroids[i]->entity->Destory();
            m_Asteroids.erase(m_Asteroids.begin() + i);
            i--;
        }
    }
}