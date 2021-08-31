#pragma once
#include "Component.h"
#include "SpriteRenderer.h"

namespace SFENG {
	class Animator : public Component
	{
	public:
		Animator();

		void AddFrame(const sf::IntRect& rect, sf::Time delay);

		void Play();
		void Stop();
		void Loop(bool v);
		void AttachSpriteRenderer(SpriteRenderer* spriteRenderer);

		bool Init() override;
		void Draw(sf::RenderWindow& window) override;
		void Update(const sf::Time& elapsedTime) override;
		void FixedUpdate(const sf::Time& elapsedTime) override;
		void HandleEvents(sf::Event& event) override;
		void Print() override;

	private:
		struct Frame {
			Frame(const sf::IntRect& bounds, sf::Time delay)
				: bounds(bounds), delay(delay)
			{}
			sf::IntRect bounds;
			sf::Time delay;
		};

		uint32_t m_FramePointer;
		sf::Clock m_Timer;
		sf::Time m_OverlappedTime;

		std::vector<Frame> m_Frames;

		bool m_Play;
		bool m_Loop;
		SpriteRenderer* m_SpriteRender;
	};
}