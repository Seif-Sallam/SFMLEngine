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

	class OnClick : public SFENG::Component 
	{
	public:
		inline bool Init() override 
		{
			m_Transform = &entity->GetCopmonent<SFENG::Transform>();
			if (entity->HasComponent<SFENG::Highlightable>())
				m_SE = &entity->GetCopmonent<SFENG::Highlightable>();
			else
				m_SE = nullptr;
			return SFENG::Component::Init();
		}
		inline void AttachSelectable(SFENG::Highlightable* se)
		{
			m_SE = se;
		}
		inline void Update(const sf::Time& time) override
		{
			shape.setSize(m_Transform->size);
			shape.setOrigin(m_Transform->size / 2.0f);
			shape.setPosition(m_Transform->position);
		}
		inline void HandleEvents(sf::Event& event) override
		{
			if (m_SE != nullptr) {
				if (m_SE->KeyPressed() == sf::Mouse::Button::Left)
				{
					std::cout << "Pressed\n";
				}
			}
			return SFENG::Component::HandleEvents(event);
		}
		inline void Draw(sf::RenderWindow& window) override 
		{
			window.draw(shape);
			return SFENG::Component::Draw(window);
		}
	private:
		SFENG::Highlightable* m_SE;
		sf::RectangleShape shape;
		SFENG::Transform* m_Transform;
	};

	CustomScene(SFENG::Engine& engine, b2World& world);
	void Main() override;
private:
	void AddSelectBox();
	void AddSprite();
	void AddCanvas();
	void AddBox(const std::string& name, const Vec2f& position, const Vec2f& size, b2BodyType type);
	void AddCircle(const std::string& name, const Vec2f& position, float radius, b2BodyType type);
	std::map<std::string, SFENG::Entity*> m_Entities;
};