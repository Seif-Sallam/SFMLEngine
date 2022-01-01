#pragma once
#include "PCH.h"

class MazeCell;
enum CellState
{
    StartCell,
    LastCell,
    CurrentCell,
    NormalCell
};

enum Direction
{
    UP = 0,
    DOWN,
    RIGHT,
    LEFT
};

class MazeCellShape : public SFENG::Component
{
public:
    MazeCellShape(int x, int y);
    bool Init() override;
    void Draw(sf::RenderWindow &window) override;
    void SetOffset(const Vec2f &offset);
    inline void SetState(CellState state) { m_State = state; }
    inline void SetVisited(bool value) { m_Visited = value; }
    inline bool IsVisited() { return m_Visited; }
    inline void SetWalls(bool *walls) { m_Wall = walls; }
    inline int GetX() { return posX; }
    inline int GetY() { return posY; }

private:
    bool *m_Wall;
    sf::RectangleShape box;
    sf::RectangleShape m_Borders[4];
    Vec2f m_Offset;
    int posX, posY;
    bool m_Visited;
    CellState m_State;
};