#pragma once
#include "PCH.h"

class PlayerController : public SFENG::Component
{
public:
	PlayerController();
	bool Init() override;
	void Update(const sf::Time&) override;
	void FixedUpdate(const sf::Time& elapsed) override;
	//void Draw(sf::RenderWindow& window) override;
	void SetController(SFENG::Controller* c);

public:
	float speed = 100.f;
private:
	SFENG::Controller* m_Controller;
};