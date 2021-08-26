#pragma once
#include "Component.h"
#include "SpriteRenderer.h"

namespace SFENG {
	class Animator : public Component
	{
	public:
		Animator();
		
		inline void AddFrame(const sf::IntRect& rect, sf::Time delay);

		inline void Play();
		inline void Stop();
		inline void Loop(bool v);
		inline void AttachSpriteRenderer(SpriteRenderer* spriteRenderer);
		
		
		inline bool Init() override;
		inline void Draw(sf::RenderWindow& window) override;
		inline void Update(const sf::Time& elapsedTime) override;
		inline void FixedUpdate(const sf::Time& elapsedTime) override;
		inline void HandleEvents(sf::Event& event) override;
		inline void Print() override;

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