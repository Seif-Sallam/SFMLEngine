#include "ParticleSystem.h"

SFENG::ParticleSystem::ParticleSystem(sf::Shape* shapeType, const Vec2f& position, const Vec2f& direction, const uint32_t& maxParticles)
	: m_ShapeType(shapeType), m_Direction(direction), m_Position(position), m_MaxParticles(maxParticles), m_Stop(false), m_Dead(false)
{
	m_Intensity = 5;
	m_AliveTime = sf::Time::Zero;
	srand(time(nullptr));
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
			for (int i = 0; i < m_Intensity; i++)
			{
				m_Particles.push_back(new Particle);
				m_Particles.back()->shape = m_ShapeType;
				m_Particles.back()->position = m_Position;
				CustomParticleInit(*m_Particles.back());
				/*float r3 = -1.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (2.0f)));
				float r4 = -1.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (2.0f)));
				m_Particles.back()->velocity = Vec2f(r3, r4);
				*/
			}
		}
	}
	for (int32_t i = m_Particles.size() - 1; i >= 0; i--) {
		CustomParticleUpdate(*m_Particles[i], time);
		//m_Particles[i]->Update(time);
		if (IsParticleFinished(i)) {
			delete m_Particles[i];;
			m_Particles.erase(m_Particles.begin() + i);
		}
	}
	if (m_Particles.size() == 0)
		m_Dead = true;
}

void SFENG::ParticleSystem::Move(const Vec2f& amount)
{
	m_Position += amount;
}

void SFENG::ParticleSystem::SetPosition(const Vec2f& pos)
{
	m_Position = pos;
}

void SFENG::ParticleSystem::SetIntensity(const int& i)
{
	if (i <= 10 && i > 0)
		m_Intensity = i;
	else if (i <= 0)
		m_Intensity = 1;
	else
		m_Intensity = 10;
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

bool SFENG::ParticleSystem::IsParticleFinished(uint32_t index)
{
	return (m_Particles[index]->alpha <= 0);
}

SFENG::ParticleSystem::Particle::Particle()
{
	this->color = sf::Color::White;
	this->position = Vec2f(0, 0);
	this->angle = 0;
	this->velocity = Vec2f(0, 0);
	switch (rand() % 3)
	{
	case 0:
		this->fadingSpeed = 100;
		break;
	case 1:
		this->fadingSpeed = 400;
		break;
	case 2:
		this->fadingSpeed = 700;
		break;
	}
}

void SFENG::ParticleSystem::Particle::Update(sf::Time time)
{
	aliveTime += time;
	alpha -= aliveTime.asSeconds() * (rand() % fadingSpeed);
	this->color = shape->getFillColor();
	this->color = sf::Color(color.r, color.g, color.b, alpha);
}

void SFENG::ParticleSystem::Particle::Draw(sf::RenderWindow& window)
{
	if (shape == nullptr) {
		std::cout << "SHAPE IS NULLPTR";
		return;
	}
	this->shape->setFillColor(this->color);
	this->shape->setPosition(this->position);
	this->shape->setRotation(this->angle);
	window.draw(*this->shape);
}