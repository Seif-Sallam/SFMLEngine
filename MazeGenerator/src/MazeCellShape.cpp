#include "MazeCellShape.h"

MazeCellShape::MazeCellShape(int x, int y)
    : posX(x), posY(y)
{
    m_Offset.Zero();
    m_State = CellState::NormalCell;
    m_Visited = false;

    m_Borders[UP].setSize(sf::Vector2f(32.f, 2.0f));
    m_Borders[DOWN].setSize(sf::Vector2f(32.f, 2.0f));
    m_Borders[RIGHT].setSize(sf::Vector2f(2.0f, 32.f));
    m_Borders[LEFT].setSize(sf::Vector2f(2.0f, 32.f));
    box.setSize(sf::Vector2f(32.0f, 32.0f));

    m_Borders[UP].setPosition(m_Offset.x + posX * 32.0f, m_Offset.y + posY * 32.0f);
    m_Borders[DOWN].setPosition(m_Offset.x + posX * 32.0f, m_Offset.y + posY * 32.0f + 32.0f);
    m_Borders[RIGHT].setPosition(m_Offset.x + posX * 32.0f + 32.0f, m_Offset.y + posY * 32.0f);
    m_Borders[LEFT].setPosition(m_Offset.x + posX * 32.0f, m_Offset.y + posY * 32.0f);
    if (posX == 0)
        m_Borders[LEFT].move(sf::Vector2f(0.0f, -1.0f));

    if (posY == 0)
        m_Borders[UP].move(sf::Vector2f(-1.0f, 0.f));

    box.setPosition(m_Offset.x + posX * 32.0f, m_Offset.y + posY * 32.0f);
}

bool MazeCellShape::Init()
{
    return Component::Init();
}

void MazeCellShape::Draw(sf::RenderWindow &window)
{
    if (m_Visited)
        box.setFillColor(sf::Color::White);
    else
        box.setFillColor(sf::Color::Red);

    if (m_State == StartCell)
        box.setFillColor(sf::Color::Green);

    if (m_State == CurrentCell)
        box.setFillColor(sf::Color::Yellow);

    if (m_State == LastCell)
        box.setFillColor(sf::Color::Cyan);

    window.draw(box);

    for (int k = 0; k < 4; k++)
    {
        if (m_Wall[k] == true)
            m_Borders[k].setFillColor(sf::Color::Blue);
        else
            m_Borders[k].setFillColor(sf::Color::White);
        window.draw(m_Borders[k]);
    }
}

void MazeCellShape::SetOffset(const Vec2f &offset)
{
    m_Offset = offset;
    m_Borders[UP].setPosition(m_Offset.x + posX * 32.0f, m_Offset.y + posY * 32.0f);
    m_Borders[DOWN].setPosition(m_Offset.x + posX * 32.0f, m_Offset.y + posY * 32.0f + 32.0f);
    m_Borders[RIGHT].setPosition(m_Offset.x + posX * 32.0f + 32.0f, m_Offset.y + posY * 32.0f);
    m_Borders[LEFT].setPosition(m_Offset.x + posX * 32.0f, m_Offset.y + posY * 32.0f);

    if (posX == 0)
        m_Borders[LEFT].move(sf::Vector2f(0.0f, -1.0f));

    if (posY == 0)
        m_Borders[UP].move(sf::Vector2f(-1.0f, 0.f));

    box.setPosition(m_Offset.x + posX * 32.0f, m_Offset.y + posY * 32.0f);
}
