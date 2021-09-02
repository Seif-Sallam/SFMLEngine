#include "../headers/FPSCounter.h"
#include "../headers/ResourceManager.h"
SFENG::FPSCounter::FPSCounter(sf::RenderWindow* window)
	: m_Window(window), m_FPS(60.f)
{
	if (window == nullptr) {
		std::cerr << "Window is a nullptr in FPSCounter\n";
		exit(0);
	}
	sf::Font& font = ResourceManager::Get().GetDefaultFont();
	m_Text.setFont(font);
	m_Text.setCharacterSize(15);
	m_Text.setFillColor(sf::Color::White);
	sf::View currentView = m_Window->getView();
	Vec2f position = currentView.getCenter() - currentView.getSize() / 2.0f; // Top LEFT
	m_Text.setPosition(position);
}

float SFENG::FPSCounter::Update()
{
	sf::View currentView = m_Window->getView();
	sf::Vector2f position = currentView.getCenter() - currentView.getSize() / 2.0f; // Top LEFT
	m_Text.setPosition(position);
	m_FrameCounter++;

	if (m_DelayTimer.getElapsedTime().asSeconds() > 0.2f)
	{
		m_FPS = m_FrameCounter / m_FPSTimer.restart().asSeconds();
		m_FrameCounter = 0;
		m_Text.setString("FPS: " + std::to_string((int)m_FPS));
		m_DelayTimer.restart();
	}
	return m_FPS;
}

void SFENG::FPSCounter::Draw(sf::RenderStates states)
{
	sf::View currentView = m_Window->getView();
	sf::Vector2f position = currentView.getCenter() - currentView.getSize() / 2.0f; // Top LEFT
	m_Text.setPosition(position);
	m_Window->draw(m_Text, states);
}