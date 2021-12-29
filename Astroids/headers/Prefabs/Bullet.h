#include "PCH.h"
#include "../Components/BulletController.h"
class Bullet
{
public:
    Bullet(SFENG::Entity *createdEntity, const Vec2f &position, const Vec2f &direction);
    SFENG::Entity *entity;
    bool IsAlive();

private:
    BulletController *m_bController;
};