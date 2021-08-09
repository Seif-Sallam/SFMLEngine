#include "../headers/ParticleSystem.h"

SFENG::ParticleSystem::ParticleSystem(sf::Shape* shapeType, const Vec2f& position, const Vec2f& direction, const uint32_t& maxParticles)
	: m_ShapeType(shapeType), m_Direction(direction), m_Position(position), m_MaxParticles(maxParticles)
{
	m_AliveTime = sf::Time::Zero;
	srand(time(0));
}

SFENG::ParticleSystem::~ParticleSystem()
{
	for (int i = 0; i < m_Particles.size(); i++)
	{
		if (m_Particles[i] != nullptr)
			delete m_Particles[i];
	}
	m_Particles.clear();
}

void SFENG::ParticleSystem::Update(sf::Time time)
{
	if (!m_Stop) {
		m_AliveTime += time;
		if (m_Particles.size() < m_MaxParticles) {
			for (int i = 0; i < 5; i++)
			{
				m_Particles.push_back(new Particle);
				m_Particles.back()->shape = m_ShapeType;
				float r3 = -1.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1.0f + 1.0f)));
				float r4 = -1.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1.0f + 1.f)));
				m_Particles.back()->velocity = Vec2f(r3, r4);
				m_Particles.back()->position = m_Position;
			}
		}
	}
	for (int32_t i = m_Particles.size() - 1; i >= 0; i--) {
		m_Particles[i]->Update(time);
		if (IsFinished(i)) {
			delete m_Particles[i];
			//std::cout << "FINISHED\n";
			m_Particles.erase(m_Particles.begin() + i);
		}
	}
}

sf::Time SFENG::ParticleSystem::AliveTime()
{
	return m_AliveTime;
}

void SFENG::ParticleSystem::Draw(sf::RenderWindow& window)
{
	for (int32_t i = m_Particles.size() - 1; i >= 0; i--)
		m_Particles[i]->Draw(window);
}

bool SFENG::ParticleSystem::IsFinished(uint32_t index)
{
	return (m_Particles[index]->alpha <= 0);
}

SFENG::ParticleSystem::Particle::Particle()
{
	this->color = sf::Color::White;
	this->position = Vec2f(0, 0);
	this->rotation = 0;
	this->velocity = Vec2f(0, 0);
}

void SFENG::ParticleSystem::Particle::Update(sf::Time time)
{
	alpha -= time.asSeconds() * (rand() % 100);
	this->color = shape->getFillColor();
	this->color = sf::Color(color.r, color.g, color.b, alpha);
	this->position += (this->velocity * time.asSeconds() * (rand() % 100));
}

void SFENG::ParticleSystem::Particle::Draw(sf::RenderWindow& window)
{
	if (shape == nullptr) {
		std::cout << "SHAPE IS NULLPTR";
		return;
	}
	this->shape->setFillColor(this->color);
	this->shape->setPosition(this->position);
	this->shape->setRotation(this->rotation);
	window.draw(*this->shape);
}
