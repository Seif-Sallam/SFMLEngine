#pragma once
#include "ECS.h"
#include "Componant.h"
#include "../Vec2.h"
#include "SFML/Graphics.hpp"

namespace SFENG {
	class Transform : public Component {
	public:
		Transform();
		Transform(float x, float y);
		Transform(Vec2f pos, Vec2f scale, float rotation);
		Transform(float x, float y, float scaleX, float scaleY, float rotation);
		virtual ~Transform() { std::cout << "In Transform Destructor\n"; }
		inline void Print() override {
			std::cout << "Transform Comp, Address: " << this << "\n";
		}
		bool Init() override;
		void Update(float deltaTime) override;
		void Draw(sf::RenderWindow* window) override;
		void HandleEvents(sf::Event* events);
		void Translate(Vec2f pos, float dt);

		Vec2f position;
		Vec2f scale;
		float rotation;
	};
}