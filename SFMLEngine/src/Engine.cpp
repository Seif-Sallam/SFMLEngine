#include "../headers/Engine.h"

SFENG::Engine::Engine(Vec2u resolution, const std::string& title)
	: m_ShouldChangeState(false), m_ShouldExit(false), m_ShouldPop(false)
	, m_TimeStep(1.0f / 60.0f)
{
	m_Window = new sf::RenderWindow(sf::VideoMode(resolution.x, resolution.y), title);
	m_Window->setVerticalSyncEnabled(true);
	m_FPSCounter = new FPSCounter(m_Window);
	m_Window->setPosition(Vec2i(m_Window->getPosition().x, 0));
	engineView = m_Window->getView();
	m_InFocus = true;
}

void SFENG::Engine::Run()
{
	sf::Clock timer;

	sf::Time lastTime = sf::Time::Zero;
	while (m_Window->isOpen() && !m_States.empty())
	{
		sf::Time time = timer.getElapsedTime();
		sf::Time elapsed = time - lastTime;
		lastTime = time;
		HandleStates();
		HandleEvent();

		if (m_InFocus)
		{
			GetCurrentState().HandleInput();
			GetCurrentState().Update(elapsed);
			m_FPSCounter->Update();
			m_Window->setView(engineView);
			Draw();
			if (this->m_PhysicsClock.getElapsedTime().asSeconds() >= m_TimeStep)
			{
				GetCurrentState().FixedUpdate(elapsed);
				m_PhysicsClock.restart();
			}
		}
		TryPop();
	}
}

void SFENG::Engine::HandleEvent()
{
	State& currentState = GetCurrentState();

	sf::Event event;

	while (m_Window->pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			ExitGame();
		if (event.type == sf::Event::Resized)
			engineView.setSize(sf::Vector2f(m_Window->getSize()));
		if (event.type == sf::Event::GainedFocus)
			m_InFocus = true;
		if (event.type == sf::Event::LostFocus)
			m_InFocus = false;

		SFENG::Keyboard::Update(event);

		if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased)
			currentState.HandleInputSlow();

		currentState.HandleEvent(event);
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
	m_Window->clear(sf::Color(192, 168, 138));
	GetCurrentState().Draw(*m_Window);
	m_FPSCounter->Draw();
	m_Window->display();
}

SFENG::State& SFENG::Engine::GetCurrentState()
{
	return *m_States.back();
}