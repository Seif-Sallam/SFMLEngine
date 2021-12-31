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
		void Update(const sf::Time &) override;
		void FixedUpdate(const sf::Time &elapsed) override;
		void Draw(sf::RenderWindow &window) override;
		void ChangeColor()
		{
			m_Shape.setFillColor(sf::Color::Blue);
		}

	private:
		sf::RectangleShape m_Shape;
		SFENG::Transform *m_Trans;
		SFENG::RigidBody2D *rb;
	};

	class CircleShape : public SFENG::Component
	{
	public:
		CircleShape();
		bool Init() override;
		void Update(const sf::Time &) override;
		void FixedUpdate(const sf::Time &elapsed) override;
		void Draw(sf::RenderWindow &window) override;

	private:
		sf::CircleShape m_Shape;
		SFENG::Transform *m_Trans;
		SFENG::RigidBody2D *rb;
	};

	class OnClick : public SFENG::Component
	{
	public:
		inline bool Init() override
		{
			m_Transform = &entity->GetComponent<SFENG::Transform>();
			if (entity->HasComponent<SFENG::Highlightable>())
				m_SE = &entity->GetComponent<SFENG::Highlightable>();
			else
				m_SE = nullptr;
			return SFENG::Component::Init();
		}
		inline void AttachSelectable(SFENG::Highlightable *se)
		{
			m_SE = se;
		}
		inline void Update(const sf::Time &time) override
		{
			shape.setSize(m_Transform->size);
			shape.setOrigin(m_Transform->size / 2.0f);
			shape.setPosition(m_Transform->position);
		}
		inline void HandleEvents(sf::Event &event) override
		{
			if (m_SE != nullptr)
			{
				if (m_SE->KeyPressed() == sf::Mouse::Button::Left)
				{
					std::cout << "Pressed\n";
				}
			}
			return SFENG::Component::HandleEvents(event);
		}
		inline void Draw(sf::RenderWindow &window) override
		{
			window.draw(shape);
			return SFENG::Component::Draw(window);
		}

	private:
		SFENG::Highlightable *m_SE;
		sf::RectangleShape shape;
		SFENG::Transform *m_Transform;
	};

	class ViewModifier : public SFENG::Component
	{
	public:
		ViewModifier(sf::View &view);
		void Update(const sf::Time &elapsed) override;
		void Draw(sf::RenderWindow &window) override;

	private:
		sf::View &m_View;
	};

	class CollisionDetector : public SFENG::Component
	{
	public:
		CollisionDetector()
		{
		}
		bool Init() override
		{
			if (this->entity->HasComponent<SFENG::BoxCollider>())
				m_BoxCollider = &this->entity->GetComponent<SFENG::BoxCollider>();
			else
				m_BoxCollider = nullptr;

			if (this->entity->HasComponent<BoxShape>())
				m_BoxShape = &this->entity->GetComponent<BoxShape>();
			else
				m_BoxShape = nullptr;
			return Component::Init();
		}
		void SetBoxCollider(SFENG::BoxCollider *boxCollider)
		{
			m_BoxCollider = boxCollider;
		}

		void FixedUpdate(const sf::Time &elapsed) override
		{
			if (m_BoxCollider)
			{
				std::list<SFENG::Entity *> collidingItems = m_BoxCollider->GetCollidingItems();
				for (auto &en : collidingItems)
				{
					if (en->GetTag() == "Movable Box")
					{
						if (m_BoxShape)
						{
							m_BoxShape->ChangeColor();
						}
					}
				}
			}
		}

	private:
		SFENG::BoxCollider *m_BoxCollider;
		BoxShape *m_BoxShape;
	};

	class BoxController : public SFENG::Component
	{
	public:
		BoxController()
		{
		}
		~BoxController()
		{
		}
		bool Init() override
		{
			if (this->entity->HasComponent<SFENG::Controller>())
				this->m_Controller = &this->entity->GetComponent<SFENG::Controller>();
			else
				m_Controller = nullptr;

			return this->Component::Init();
		}
		void Update(const sf::Time &elapsed)
		{
			if (m_Controller)
			{
				if (SFENG::Keyboard::IsKeyPressed(sf::Keyboard::W))
				{
					m_Controller->Move(Vec2f(0.f, -250.f * elapsed.asSeconds()));
				}
				if (SFENG::Keyboard::IsKeyPressed(sf::Keyboard::S))
				{
					m_Controller->Move(Vec2f(0.f, 250.f * elapsed.asSeconds()));
				}
				if (SFENG::Keyboard::IsKeyPressed(sf::Keyboard::A))
				{
					m_Controller->Move(Vec2f(-250.f * elapsed.asSeconds(), 0.f));
				}
				if (SFENG::Keyboard::IsKeyPressed(sf::Keyboard::D))
				{
					m_Controller->Move(Vec2f(250.f * elapsed.asSeconds(), 0.f));
				}
			}
		}
		void SetController(SFENG::Controller *controller)
		{
			m_Controller = controller;
		}

	private:
		SFENG::Controller *m_Controller;
	};

	CustomScene(SFENG::Engine &engine);

private:
	void Main();
	void AddSelectBox();
	void AddSprite();
	void AddCanvas();
	void AddBox(const std::string &name, const Vec2f &position, const Vec2f &size, b2BodyType type);
	void AddCircle(const std::string &name, const Vec2f &position, float radius, b2BodyType type);
	std::map<std::string, SFENG::Entity *> m_Entities;
};