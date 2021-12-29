#pragma once
#include "PCH.h"

class PlayerController : public SFENG::Component
{
public:
	PlayerController();
	bool Init() override;
	void Update(const sf::Time &) override;
	void FixedUpdate(const sf::Time &elapsed) override;
	void SetController(SFENG::Controller *c);
	void SetAnimator(SFENG::Animator *animator);

public:
	float speed = 100.f;

private:
	enum Direction
	{
		FRONT,
		LEFT,
		RIGHT
	};
	void HandleAnimations(const sf::Time &elapsed);
	void HandleControls(const sf::Time &elapsed);
	Direction m_CurrentDirection;
	bool m_Thrusting;
	SFENG::Transform *m_Transform;
	SFENG::Controller *m_Controller;
	SFENG::Animator *m_Animator;
	bool m_Alive;
	float m_Angle;
	const float m_RotationSpeed;

	Vec2f m_Velocity;
	const float m_MaxSpeed;
};