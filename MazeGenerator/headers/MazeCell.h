#pragma once
#include "PCH.h"
#include "MazeCellShape.h"

class MazeCell
{

public:
    MazeCell(SFENG::Entity *createdEntity, int x, int y);
    ~MazeCell();
    void SetState(CellState state);
    void SetOffset(const Vec2f &offset);
    bool *&GetWalls();
    void SetVisited(bool value);
    bool IsVisited();
    inline int GetX() { return m_MazeCellShape->GetX(); }
    inline int GetY() { return m_MazeCellShape->GetY(); }
    SFENG::Entity *entity;

private:
    MazeCellShape *m_MazeCellShape;
    bool *m_Walls;
};