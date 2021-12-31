#pragma once
#include "Animation.h"
#include "Component.h"
#include <map>

namespace SFENG
{
	class Animator : public Component
	{
		friend Animation;

	public:
		Animator();
		Animator(const Animator &a);
		~Animator();
		void AttachSpriteRenderer(SpriteRenderer *sr);
		Animation *AddAnimation(const std::string &animName);
		Animation *GetAnimation(const std::string &animName);
		void SetActiveAnimation(const std::string &animName);
		bool Init() override;
		void Update(const sf::Time &elapsedTime) override;
		void Print() override;

	private:
		SpriteRenderer *m_SpriteRenderer;
		std::map<std::string, Animation> m_Animations;
		std::string m_ActiveAnimation, m_LastAnimation;
		bool m_Reset;
	};
}