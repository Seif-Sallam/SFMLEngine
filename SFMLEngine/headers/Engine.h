#pragma once
#include "PCH.h"
#include "State.h"
#include "FPSCounter.h"

namespace SFENG {
	class Engine
	{
	public:
		void Run();
		sf::View engineView;
		inline sf::RenderWindow& GetWindow() { return *m_Window; }
		void ExitGame();
	protected:
		Engine(Vec2u resolution = Vec2u(800, 600), const std::string& title = "Title");
		~Engine();
		virtual void HandleStates() {}
		void PushStartingState(std::unique_ptr<State> state);
		void ShouldChangeState(std::unique_ptr<State> change);
		
		void PopState();
	private:
		template<class T, class... Args>
		void PushState(Args&&... args);
		void PushState(std::unique_ptr<State> state);
		void HandleEvent();
		void TryPop();
		void Draw();
		State& GetCurrentState();

		std::vector<std::unique_ptr<State>> m_States;
		std::unique_ptr<State> m_Change;

		sf::RenderWindow* m_Window;
		FPSCounter* m_FPSCounter;

		bool m_ShouldChangeState;
		bool m_ShouldExit;
		bool m_ShouldPop;
		bool m_InFocus;
		
	};

	template<class T, class ...Args>
	inline void Engine::PushState(Args && ...args)
	{
		PushState(std::make_unique<T>(std::forward<Args>(args)...));
	}
}