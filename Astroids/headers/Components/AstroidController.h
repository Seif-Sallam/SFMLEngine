#pragma once
#include "PCH.h"

class AstroidController : public SFENG::Component
{
public:
    AstroidController(const Vec2f &position, bool big, const Vec2f &direction = Vec2f(1.f, 0.f));
    ~AstroidController();
    bool Init() override;
    void Update(const sf::Time &) override;

    float speed;
    bool alive;

private:
    bool m_Big;
    Vec2f m_Position;
    SFENG::Transform *m_Transform;
    Vec2f m_Direction;
    float m_Angle;
    sf::Time totalTime;
};