#include "../headers/LevelScene.h"
#include "../headers/Prefabs/SpaceShip.h"
#include "../headers/Components/AstroidsCreator.h"
LevelScene::LevelScene(SFENG::Engine &engine)
    : Scene(engine)
{
    this->m_Engine.SetGravity(Vec2f(0.f, 0.f));
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
    // m_LCManager.CreateEntity("ViewModifier")->AddComponent<ViewModifier>(this->m_Engine.engineView);

    {
        SFENG::ResourceManager::AddTexture("rsc/textures/background0.jpg", "Background");
        SFENG::ResourceManager::AddTexture("rsc/textures/rock.png", "BIG_Astroid");
        SFENG::ResourceManager::AddTexture("rsc/textures/rock_small.png", "SMALL_Astroid");
        SFENG::ResourceManager::AddTexture("rsc/textures/explosions/type_C.png", "Explosion");
        SFENG::Entity *background = m_LCManager.CreateEntity("Background");
        auto &sp = background->AddComponent<SFENG::SpriteRenderer>();
        sp.AttachTexture("Background");
        auto &trans = background->GetComponent<SFENG::Transform>();
        Vec2u windowSize = m_Engine.GetWindow().getSize();
        SFENG::Engine::GetWindow().setTitle("Astroids");
        trans.position = Vec2f(windowSize.x / 2.f, windowSize.y / 2.f);
    }

    SpaceShip player(m_LCManager.CreateEntity("Player"));
    SFENG::Entity *astroids = m_LCManager.CreateEntity("AstroidManager");
    astroids->AddComponent<AstroidsCreator>();
}