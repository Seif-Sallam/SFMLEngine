#include "../headers/MazeCell.h"
#include "../headers/MazeCellShape.h"

MazeCell::MazeCell(SFENG::Entity *createdEntity, int x, int y)
{
    entity = createdEntity;

    m_MazeCellShape = &createdEntity->AddComponent<MazeCellShape>(x, y);
    m_Walls = new bool[4];
    for (int i = 0; i < 4; i++)
        m_Walls[i] = true;
    m_MazeCellShape->SetWalls(m_Walls);
    this->entity->GetComponent<SFENG::Transform>().position = Vec2f(x * 32.0f, y * 32.0f);
}

void MazeCell::SetState(CellState state)
{
    this->m_MazeCellShape->SetState(state);
}

void MazeCell::SetOffset(const Vec2f &offset)
{
    this->m_MazeCellShape->SetOffset(offset);
    this->entity->GetComponent<SFENG::Transform>().position = Vec2f(m_MazeCellShape->GetX() * 32.0f + offset.x, m_MazeCellShape->GetY() * 32.0f + offset.y);
}

bool *&MazeCell::GetWalls()
{
    return this->m_Walls;
}

void MazeCell::SetVisited(bool value)
{
    this->m_MazeCellShape->SetVisited(value);
}

bool MazeCell::IsVisited()
{
    return this->m_MazeCellShape->IsVisited();
}

MazeCell::~MazeCell()
{
    this->entity->Destory();
    delete[] m_Walls;
}