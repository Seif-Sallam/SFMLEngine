#include "LevelScene.h"
#include "MazeController.h"
#include "MazeGenerator.h"

LevelScene::LevelScene(SFENG::Engine &engine)
    : Scene(engine, true)
{
    AddMain();
}

LevelScene::~LevelScene()
{
}

class ViewModifier : public SFENG::Component
{
public:
    ViewModifier(sf::View &view);
    void Update(const sf::Time &elapsed) override;
    void Draw(sf::RenderWindow &window) override;

private:
    sf::View &m_View;
};

ViewModifier::ViewModifier(sf::View &view)
    : m_View(view)
{
}

void ViewModifier::Update(const sf::Time &elapsed)
{
    if (SFENG::Keyboard::IsKeyPressed(sf::Keyboard::Left))
    {
        m_View.move(-250.f * elapsed.asSeconds(), 0.f);
    }
    if (SFENG::Keyboard::IsKeyPressed(sf::Keyboard::Right))
    {
        m_View.move(250.f * elapsed.asSeconds(), 0.f);
    }
    if (SFENG::Keyboard::IsKeyPressed(sf::Keyboard::Up))
    {
        m_View.move(0.f, -250.f * elapsed.asSeconds());
    }
    if (SFENG::Keyboard::IsKeyPressed(sf::Keyboard::Down))
    {
        m_View.move(0.f, 250.f * elapsed.asSeconds());
    }
}
void ViewModifier::Draw(sf::RenderWindow &window)
{
    window.setView(m_View);
}

void LevelScene::AddMain()
{
    SFENG::Entity *maze = this->m_LCManager.CreateEntity("MazeGenerator");
    maze->AddComponent<MazeGenerator>();
    maze->AddComponent<MazeController>();
}