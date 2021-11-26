#include "ParticleFountain.h"

SFENG::ParticleFountain::ParticleFountain(sf::Shape* shapeType, const Vec2f& position, const Vec2f& direction, const uint32_t& maxParticles)
	: ParticleSystem(shapeType, position, direction, maxParticles)
{
	m_Angle = 10.f;
	m_Width = 5;
}

void SFENG::ParticleFountain::SetWidth(int width)
{
	m_Width = width;
}

void SFENG::ParticleFountain::SetAngle(float angle)
{
	m_Angle = angle;
}

void SFENG::ParticleFountain::CustomParticleInit(Particle& p)
{
	//float randomVelocity = 2 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1.0f)));
	p.radius = float(rand() % m_Width + 5);
	p.right = bool(rand() % 2);
	p.w = sqrtf(2) / p.radius;
}

//Some bullshit is happening here
void SFENG::ParticleFountain::CustomParticleUpdate(Particle& p, sf::Time t)
{
	p.Update(t);
	p.angle = p.aliveTime.asMilliseconds() * p.w;
	float radianAngle = toRadian(p.angle + m_Angle);
	Vec2f movement = Vec2f(cosf(radianAngle) * p.radius, -sinf(radianAngle) * p.radius);
	if (p.right)
		movement.x *= -1;
	p.position += movement;
}