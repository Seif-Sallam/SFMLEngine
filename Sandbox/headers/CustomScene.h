#pragma once
#include "PCH.h"

class CustomScene : public SFENG::Scene 
{
public:
	class BoxShape : public SFENG::Component 
	{
	public:
		BoxShape();
		bool Init() override;
		void Update(const sf::Time&) override;
		void FixedUpdate(const sf::Time& elapsed) override;
		void Draw(sf::RenderWindow& window) override;
	private:
		sf::RectangleShape m_Shape;
		SFENG::Transform* m_Trans;
		SFENG::RigidBody2D* rb;
	};

	class CircleShape : public SFENG::Component {
	public:
		CircleShape();
		bool Init() override;
		void Update(const sf::Time&) override;
		void FixedUpdate(const sf::Time& elapsed) override;
		void Draw(sf::RenderWindow& window) override;
	private:
		sf::CircleShape m_Shape;
		SFENG::Transform* m_Trans;
		SFENG::RigidBody2D* rb;
	};

	CustomScene(SFENG::Engine& engine, b2World& world);
	void Main() override;
	void AddBox(const std::string& name, const Vec2f& position, const Vec2f& size, b2BodyType type);
	void AddCircle(const std::string& name, const Vec2f& position, float radius, b2BodyType type);
private:
	std::map<std::string, SFENG::Entity*> m_Entities;
};