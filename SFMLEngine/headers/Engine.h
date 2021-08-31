#pragma once
#include "Scene.h"
#include "FPSCounter.h"
#include "Keyboard.h"
#include <memory>
#include <vector>
#include <map>
#include "box2d/box2d.h"

namespace SFENG {
	class Engine
	{
	public:
		void Run();
		inline sf::RenderWindow& GetWindow() { return *m_Window; }
		void ExitGame();
		void SetGravity(const Vec2f& gravity);
		const Vec2f& GetGravity();
	protected:
		Engine(Vec2u resolution = Vec2u(800, 600), const std::string& title = "Title");
		~Engine();
		void PushStartingScene(std::unique_ptr<Scene> state);
		void ShouldChangeScene(std::unique_ptr<Scene> change);
		void PopState();
		virtual void HandleScenes() {}
		template<class T, class... Args>
		void PushScene(Args&&... args);
		void PushScene(std::unique_ptr<Scene> state);
	private:
		void HandleEvent();
		void TryPop();
		void Draw();
		Scene& GetCurrentScene();

	public:
		sf::View engineView;

	private:
		std::vector<std::unique_ptr<Scene>> m_States;
		std::unique_ptr<Scene> m_Change;

		sf::RenderWindow* m_Window;
		FPSCounter* m_FPSCounter;

		sf::Clock m_PhysicsClock;
		const float m_TimeStep;
		bool m_ShouldChangeState;
		bool m_ShouldExit;
		bool m_ShouldPop;
		bool m_InFocus;

		Vec2f m_Gravity;
	protected:
		b2World* m_PhysicsWorld;
	};

	template<class T, class ...Args>
	inline void Engine::PushScene(Args && ...args)
	{
		PushScene(std::make_unique<T>(std::forward<Args>(args)...));
	}
}