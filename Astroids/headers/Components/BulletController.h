#pragma once
#include "PCH.h"

class BulletController : public SFENG::Component
{
public:
    BulletController(const Vec2f &position, const Vec2f &direction = Vec2f(1.f, 0.f));
    ~BulletController();
    bool Init() override;
    void Update(const sf::Time &) override;

    float speed;
    bool alive;

private:
    Vec2f m_Position;
    SFENG::Transform *m_Transform;
    Vec2f m_Direction;
};