#pragma once
#include "SFML/Graphics.hpp"
#include "Vec2.h"
#include <random>

namespace SFENG 
{

	class ParticleSystem 
	{
	public:
		ParticleSystem(sf::Shape* shapeType = nullptr, const Vec2f& position = Vec2f(0,0), 
			const Vec2f& direction = Vec2f(0, -1), const uint32_t& maxParticles = 1000);
		~ParticleSystem();
		void Update(sf::Time time);
		sf::Time AliveTime();
		void Draw(sf::RenderWindow& window);
		inline void Stop() { m_Stop = true; }
	private:
		bool IsFinished(uint32_t index);
		struct Particle
		{
			Vec2f position;
			Vec2f velocity;
			float rotation;
			sf::Shape* shape;
			sf::Color color = sf::Color(255,255,255,255);
			int alpha = 255; 
			void Update(sf::Time time);
			void Draw(sf::RenderWindow& window);
			Particle();
		};

		std::vector<Particle*> m_Particles;
		uint32_t m_MaxParticles;
		sf::Shape* m_ShapeType;
		Vec2f m_Direction;
		Vec2f m_Position;
		sf::Time m_AliveTime;
		bool m_Stop;
	};
}