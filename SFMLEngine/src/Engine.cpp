#include "../headers/Engine.h"

SFENG::Engine::Engine(Vec2u resolution, const std::string& title)
	: m_ShouldChangeState(false), m_ShouldExit(false), m_ShouldPop(false)
{
	m_Window = new sf::RenderWindow(sf::VideoMode(resolution.x, resolution.y), title);
	m_Window->setVerticalSyncEnabled(true);
	m_FPSCounter = new FPSCounter(m_Window);
	m_Window->setPosition(Vec2i(m_Window->getPosition().x, 0));
	view = m_Window->getView();
}

void SFENG::Engine::Run()
{
	constexpr unsigned int TPS = 30;
	const sf::Time timePerUpdate = sf::seconds(1.0f / float(TPS));
	unsigned int ticks = 0;

	sf::Clock timer;

	sf::Time lastTime = sf::Time::Zero;
	sf::Time lag = sf::Time::Zero;
	while (m_Window->isOpen() && !m_States.empty())
	{

		sf::Time time = timer.getElapsedTime();
		sf::Time elapsed = time - lastTime;
		lastTime = time;
		lag += elapsed;
		HandleStates();
		HandleEvent();

		m_Window->setView(view);
		GetCurrentState().HandleInput();
		GetCurrentState().Update(elapsed);
		m_FPSCounter->Update();
		GetCurrentState().FixedUpdate(elapsed);
		Draw();
		TryPop();
	}

}

SFENG::Engine::~Engine()
{
	delete m_FPSCounter;
	delete m_Window;
}

void SFENG::Engine::PushStartingState(std::unique_ptr<State> state)
{
	PushState(std::move(state));
}

void SFENG::Engine::ShouldChangeState(std::unique_ptr<State> change)
{
	m_ShouldChangeState = true;
	m_Change = std::move(change);
}

void SFENG::Engine::PopState()
{
	m_ShouldPop = true;
}

void SFENG::Engine::ExitGame()
{
	m_ShouldPop = true;
	m_ShouldExit = true;
}

void SFENG::Engine::PushState(std::unique_ptr<State> state)
{
	m_States.push_back(std::move(state));
}

void SFENG::Engine::HandleEvent()
{
	State& currentState = GetCurrentState();

	sf::Event event;

	while (m_Window->pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			ExitGame();
		SFENG::Keyboard::Update(event);
		currentState.HandleEvent(event);
	}

}

void SFENG::Engine::TryPop()
{
	if (m_ShouldPop)
	{
		m_ShouldPop = false;
		if (m_ShouldExit)
		{
			m_States.clear();
			return;
		}
		else if (m_ShouldChangeState)
		{
			m_ShouldChangeState = false;
			m_States.pop_back();
			PushState(std::move(m_Change));
			return;
		}
		else
			m_States.pop_back();
	}
}

void SFENG::Engine::Draw()
{
	m_Window->clear(sf::Color(192,168,138));
	GetCurrentState().Draw(*m_Window);
	m_FPSCounter->Draw();
	m_Window->display();
}

SFENG::State& SFENG::Engine::GetCurrentState()
{
	return *m_States.back();
}