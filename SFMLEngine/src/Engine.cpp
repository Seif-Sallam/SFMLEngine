#include "Engine.h"
sf::RenderWindow *SFENG::Engine::m_Window = nullptr;
b2World *SFENG::Engine::m_PhysicsWorld = nullptr;
SFENG::PhysicsListener SFENG::Engine::m_PhysicsListener;

SFENG::Engine::Engine(Vec2u resolution, const std::string &title)
	: m_ShouldChangeState(false), m_ShouldExit(false), m_ShouldPop(false), m_InFocus(true), m_TimeStep(1.0f / 60.0f), m_Gravity(Vec2f(0.0f, 9.81f))
{
	m_Window = new sf::RenderWindow(sf::VideoMode(resolution.x, resolution.y), title);

	m_Window->setVerticalSyncEnabled(true);
	m_Window->setPosition(Vec2i(m_Window->getPosition().x, 0));
	m_FPSCounter = new FPSCounter(m_Window);
	engineView = m_Window->getView();
	m_PhysicsWorld = new b2World(m_Gravity);

	ImGui::SFML::Init(*m_Window);
	m_PhysicsWorld->SetContactListener(&m_PhysicsListener);
}

void SFENG::Engine::Run()
{
	sf::Clock timer;
	sf::Time lastTime = sf::Time::Zero;
	while (m_Window->isOpen() && !m_States.empty())
	{
		Scene &thisScene = GetCurrentScene();
		sf::Time time = timer.getElapsedTime();
		sf::Time elapsed = time - lastTime;
		if (elapsed.asSeconds() < 0)
			elapsed = sf::milliseconds(1);

		lastTime = time;
		// ImGui::NewFrame();
		HandleScenes();
		HandleEvent();

		if (m_InFocus)
		{
			ImGui::SFML::Update(*this->m_Window, elapsed);
			m_FPSCounter->Update();
			// ImGui::Begin("Hello, World");

			// ImGui::Button("A Button over here");

			// ImGui::End();
			// ImGui::Begin("Hello, World TWO");

			// ImGui::Button("A Button over there");

			// ImGui::End();

			thisScene.Update(elapsed);

			m_Window->setView(engineView);

			Draw();

			m_PhysicsListener.Update();
			m_PhysicsWorld->Step(m_TimeStep, 6, 2);

			if (this->m_PhysicsClock.getElapsedTime().asSeconds() >= m_TimeStep)
			{
				thisScene.FixedUpdate(elapsed);
				m_PhysicsClock.restart();
			}
			thisScene.Refresh();
		}
		// ImGui::EndFrame();
		TryPop();
	}
}

void SFENG::Engine::HandleEvent()
{
	Scene &currentState = GetCurrentScene();

	sf::Event event;

	while (m_Window->pollEvent(event))
	{
		ImGui::SFML::ProcessEvent(event);
		if (event.type == sf::Event::Closed)
			ExitGame();
		if (event.type == sf::Event::Resized)
		{
			engineView.setSize(sf::Vector2f(m_Window->getSize()));
			engineView.setCenter(engineView.getSize() / 2.f);
		}
		if (event.type == sf::Event::GainedFocus)
			m_InFocus = true;
		if (event.type == sf::Event::LostFocus)
			m_InFocus = false;

		SFENG::Keyboard::Update(event);
		SFENG::Mouse::Update(event);

		currentState.HandleEvents(event);
	}
}

SFENG::Engine::~Engine()
{
	m_Window->close();
	ImGui::SFML::Shutdown();
	delete m_FPSCounter;
	delete m_Window;
}

void SFENG::Engine::PushStartingScene(std::unique_ptr<Scene> state)
{
	PushScene(std::move(state));
}

void SFENG::Engine::ShouldChangeScene(std::unique_ptr<Scene> change)
{
	m_ShouldChangeState = true;
	m_Change = std::move(change);
}

void SFENG::Engine::PopState()
{
	m_ShouldPop = true;
}
b2World &SFENG::Engine::GetPhysicsWorld()
{
	return *m_PhysicsWorld;
}

void SFENG::Engine::ExitGame()
{
	m_ShouldPop = true;
	m_ShouldExit = true;
}

void SFENG::Engine::SetGravity(const Vec2f &gravity)
{
	m_Gravity = gravity;
	m_PhysicsWorld->SetGravity(m_Gravity);
}

const Vec2f &SFENG::Engine::GetGravity()
{
	return m_Gravity;
}

void SFENG::Engine::PushScene(std::unique_ptr<Scene> state)
{
	m_States.push_back(std::move(state));
	LCM::s_OnGoingLCM = &m_States.back()->m_LCManager;
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
			PushScene(std::move(m_Change));
			return;
		}
		else
		{
			m_States.pop_back();
			if (m_States.size() > 0)
				LCM::s_OnGoingLCM = &m_States.back()->m_LCManager;
		}
	}
}

void SFENG::Engine::Draw()
{
	m_Window->clear(sf::Color(192, 168, 138));
	GetCurrentScene().Draw(*m_Window);
	m_FPSCounter->Draw();
	ImGui::SFML::Render(*m_Window);
	m_Window->display();
}

SFENG::Scene &SFENG::Engine::GetCurrentScene()
{
	return *m_States.back();
}

const std::list<std::pair<SFENG::Entity *, SFENG::Entity *>> &SFENG::Engine::GetContactList()
{
	return m_PhysicsListener.GetContactList();
}
