#pragma once
#include "ParticleSystem.h"
#define _USE_MATH_DEFINES
#include <math.h>
namespace SFENG {

	class UFParticleSystem : public ParticleSystem
	{
	public:
		UFParticleSystem(sf::Shape* shapeType = nullptr, const Vec2f& position = Vec2f(0, 0),
			const Vec2f& direction = Vec2f(0, -1), const uint32_t& maxParticles = 1000);
		void SetAngle(float anlge);

		void CustomParticleInit(Particle& p) override;
		void CustomParticleUpdate(Particle& p, sf::Time t) override;
	private:
		inline float toRadian(float degree) { return ((degree / 180.0f) * M_PI); }
		float m_Angle;
		float w;
		float m_Radius;
	};
}
