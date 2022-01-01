#include "Engine.h"
namespace SFENG
{

	sf::RenderWindow *Engine::m_Window = nullptr;
	b2World *Engine::m_PhysicsWorld = nullptr;
	PhysicsListener Engine::m_PhysicsListener;

	Engine::Engine(Vec2u resolution, const std::string &title)
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

	void Engine::Run()
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

			HandleScenes();
			HandleEvent();

			ImGui::SFML::Update(*this->m_Window, elapsed);
			if (m_InFocus)
			{
				m_FPSCounter->Update();
				// ImGui::Begin("Hello, World");

				// ImGui::Button("A Button over here");

				// ImGui::End();
				// ImGui::Begin("Hello, World TWO");

				// ImGui::Button("A Button over there");

				// ImGui::End();
				thisScene.ImGuiLayer();

				thisScene.Update(elapsed);
				m_Window->setView(engineView);

				m_PhysicsListener.Update();
				m_PhysicsWorld->Step(m_TimeStep, 6, 2);

				if (this->m_PhysicsClock.getElapsedTime().asSeconds() >= m_TimeStep)
				{
					thisScene.FixedUpdate(elapsed);
					m_PhysicsClock.restart();
				}
				thisScene.Refresh();
			}
			Draw();
			TryPop();
		}
	}

	void Engine::HandleEvent()
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

			Keyboard::Update(event);
			Mouse::Update(event);

			currentState.HandleEvents(event);
		}
	}

	Engine::~Engine()
	{
		m_Window->close();
		ImGui::SFML::Shutdown();
		delete m_FPSCounter;
		delete m_Window;
	}

	void Engine::SetLCMToScene(Scene *scene)
	{
		LCM::s_OnGoingLCM = &scene->m_LCManager;
	}
	void Engine::PushStartingScene(std::unique_ptr<Scene> state)
	{
		PushScene(std::move(state));
	}

	void Engine::ShouldChangeScene(std::unique_ptr<Scene> change)
	{
		m_ShouldChangeState = true;
		m_Change = std::move(change);
	}

	void Engine::PopState()
	{
		m_ShouldPop = true;
	}
	b2World &Engine::GetPhysicsWorld()
	{
		return *m_PhysicsWorld;
	}

	void Engine::ExitGame()
	{
		m_ShouldPop = true;
		m_ShouldExit = true;
	}

	void Engine::SetGravity(const Vec2f &gravity)
	{
		m_Gravity = gravity;
		m_PhysicsWorld->SetGravity(m_Gravity);
	}

	const Vec2f &Engine::GetGravity()
	{
		return m_Gravity;
	}

	void Engine::PushScene(std::unique_ptr<Scene> state)
	{
		m_States.push_back(std::move(state));
		LCM::s_OnGoingLCM = &m_States.back()->m_LCManager;
	}

	void Engine::TryPop()
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

	void Engine::Draw()
	{
		m_Window->clear(sf::Color(192, 168, 138));
		GetCurrentScene().Draw(*m_Window);
		m_FPSCounter->Draw();
		ImGui::SFML::Render(*m_Window);
		m_Window->display();
	}

	Scene &Engine::GetCurrentScene()
	{
		return *m_States.back();
	}

	const std::list<std::pair<Entity *, Entity *>> &Engine::GetContactList()
	{
		return m_PhysicsListener.GetContactList();
	}
}