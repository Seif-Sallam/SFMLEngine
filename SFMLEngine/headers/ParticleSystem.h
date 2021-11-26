#pragma once
#include "SFML/Graphics.hpp"
#include "Vec2.h"
#include <math.h>

namespace SFENG
{
	class ParticleSystem
	{
	public:
		ParticleSystem(sf::Shape* shapeType = nullptr, const Vec2f& position = Vec2f(0, 0),
			const Vec2f& direction = Vec2f(0, -1), const uint32_t& maxParticles = 1000);
		~ParticleSystem();
		void Update(sf::Time time);
		void Move(const Vec2f& amount);
		void SetPosition(const Vec2f& pos);
		void SetIntensity(const int& i);
		sf::Time AliveTime();
		void Draw(sf::RenderWindow& window);
		inline bool IsDead() { return m_Dead; }
		inline void Stop() { m_Stop = true; }

	protected:
		struct Particle
		{
			Vec2f position;
			Vec2f velocity;
			Vec2f direction;
			float angle;
			float radius;
			float w;
			bool right;
			int fadingSpeed;
			sf::Shape* shape;
			sf::Color color = sf::Color(255, 255, 255, 255);
			int alpha = 255;

			sf::Time aliveTime;

			Particle();
			void Update(sf::Time time);
			void Draw(sf::RenderWindow& window);
		};

		bool IsParticleFinished(uint32_t index);
		virtual void CustomParticleInit(Particle& p) = 0;
		virtual void CustomParticleUpdate(Particle& p, sf::Time t) = 0;

		sf::Shape* m_ShapeType;
		Vec2f m_Position;
		Vec2f m_Direction;
		uint32_t m_MaxParticles;
		bool m_Stop, m_Dead;
		sf::Time m_AliveTime;
		int m_Intensity;

		std::vector<Particle*> m_Particles;
	};
}