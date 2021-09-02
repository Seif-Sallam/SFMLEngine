#pragma once
#include <string>
#include <vector>
#include "SFML/Graphics.hpp"

namespace SFENG {
	class SpriteRenderer;
	class Animation
	{
	public:
		Animation();
		Animation(const std::string& name);
		Animation(const Animation& a);
		void AddFrame(const sf::IntRect& rect, sf::Time delay);
		void SetName(const std::string& name);
		void Play();
		void Stop();
		void Loop(bool v);
		void Reset();
		void AttachSpriteRenderer(SpriteRenderer* spriteRenderer);

		void Update(const sf::Time& elapsedTime);
		void Print();
		inline std::string GetName() { return m_Name; }
	private:
		inline void SetSpriteRenderer(SpriteRenderer* sp) { m_SpriteRender = sp; }
		std::string m_Name;
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