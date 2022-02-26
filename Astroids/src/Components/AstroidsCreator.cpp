#include "../headers/Components/AstroidsCreator.h"
#include "../headers/Prefabs/Astroid.h"
#include "../headers/Prefabs/Explosion.h"
#include "../headers/Components/AstroidController.h"

AstroidsCreator::AstroidsCreator()
    : m_AstroidsCount(0), m_PassedTime(sf::Time::Zero), m_RateOfSpawn(sf::seconds(1.f))
{
    m_RandomGenerator.seed(time(0));
}

AstroidsCreator::~AstroidsCreator()
{
}

bool AstroidsCreator::Init()
{
    return this->Component::Init();
}

void AstroidsCreator::Update(const sf::Time &elapsed)
{
    static std::uniform_int_distribution<int> dist(0, 1);
    static std::uniform_real_distribution<float> positionX(100.f, 1300.f);
    static std::uniform_real_distribution<float> positionY(25.f, 800.f);
    static std::uniform_real_distribution<float> direction(-1.f, 1.f);
    m_PassedTime += elapsed;
    if (m_PassedTime >= m_RateOfSpawn && m_Astroids.size() < 15)
    {
        m_PassedTime = sf::seconds(0.f);
        m_AstroidsCount++;
        Vec2f position = Vec2f(positionX(m_RandomGenerator), positionY(m_RandomGenerator));
        Vec2f directionVec = Vec2f(direction(m_RandomGenerator), direction(m_RandomGenerator));
        bool big = dist(m_RandomGenerator);
        SFENG::Entity *astroidEntity = SFENG::LCM::InstantiateObject("Astroid#" + std::to_string(m_AstroidsCount));
        m_Astroids.push_back(std::make_unique<Astroid>(
            astroidEntity, position, directionVec, big));

        auto &controller = astroidEntity->AddComponent<SFENG::Controller>();
        auto &astroidController = astroidEntity->GetComponent<AstroidController>();
        astroidController.SetController(&controller);
    }
    HandleDeadAstroids();
    return this->Component::Update(elapsed);
}

void AstroidsCreator::HandleDeadAstroids()
{
    for (int i = 0; i < m_Astroids.size(); i++)
    {
        if (!m_Astroids[i]->IsAlive())
        {
            std::cout << "Deleted\n";
            Vec2f pos = m_Astroids[i]->entity->GetComponent<SFENG::Transform>().position;
            Explosion e(SFENG::LCM::InstantiateObject("Explosion#" + std::to_string(m_AstroidsCount - 1)), pos);
            m_Astroids[i]->entity->Destory();
            m_Astroids.erase(m_Astroids.begin() + i);
            i--;
        }
    }
}