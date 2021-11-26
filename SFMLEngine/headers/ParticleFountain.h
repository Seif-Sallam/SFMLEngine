#pragma once
#include "ParticleSystem.h"
#define _USE_MATH_DEFINES
#include <math.h>
namespace SFENG {
	class ParticleFountain : public ParticleSystem
	{
	public:
		ParticleFountain(sf::Shape* shapeType = nullptr, const Vec2f& position = Vec2f(0, 0),
			const Vec2f& direction = Vec2f(0, -1), const uint32_t& maxParticles = 1000);
		void SetWidth(int width);
		void SetAngle(float angle);
		void CustomParticleInit(Particle& p) override;
		void CustomParticleUpdate(Particle& p, sf::Time t) override;
	private:
		inline float toRadian(float degree) { return float((degree / 180.0f) * M_PI); }
		int m_Width;
		//float m_Angle;
		float m_Angle;
	};
}
