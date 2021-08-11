#include "../headers/UFParticleSystem.h"

SFENG::UFParticleSystem::UFParticleSystem(sf::Shape* shapeType, const Vec2f& position, const Vec2f& direction, const uint32_t& maxParticles)
	: ParticleSystem(shapeType, position, direction, maxParticles)
{
	m_Angle = 1000.f;
	m_Radius = 5.f;
}

void SFENG::UFParticleSystem::SetAngle(float angle)
{
	m_Angle = angle;
}

void SFENG::UFParticleSystem::CustomParticleInit(Particle& p)
{
	float randomVelocity = fabsf(-1.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (2.0f))));
	w = sqrtf(randomVelocity) / m_Radius;
	std::cout << w << std::endl;
	//p.velocity = Vec2f(randomVelocity, randomVelocity);
}

//Some bullshit is happening here
void SFENG::UFParticleSystem::CustomParticleUpdate(Particle& p, sf::Time t)
{
	float randomAngle = -1.0f * m_Angle + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (2 * m_Angle)));
	p.Update(t);
	float currentAngle = p.aliveTime.asMilliseconds() * w;
	float radianAngle = toRadian(currentAngle);
	p.position += Vec2f(cosf(radianAngle) * m_Radius, sinf(radianAngle) * m_Radius);
	//std::cout << p.position << std::endl;
}
