#pragma once
#include "PCH.h"
#include <stack>
#include "../headers/MazeCell.h"
class MazeGenerator : public SFENG::Component
{
public:
    MazeGenerator();
    ~MazeGenerator() override;
    bool Init() override;
    void ImGuiLayer() override;
    void Draw(sf::RenderWindow &window) override;
    void SetWidthAndHeight(int width, int height);
    int GetWidth();
    int GetHeight();
    void Reset();
    bool IsRunning();
    void Run(bool v);
    int startX, startY;
    void TakeStep();
    void SetOffset(const Vec2f &offset);
    MazeCell *GetCurrentCell();

private:
    void DrawCell(sf::RenderWindow &window, int i, int j, sf::RectangleShape &shape, sf::RectangleShape borders[4]);
    std::vector<Direction> GetFreeCells(int i, int j);
    int lastX, lastY;
    bool m_Running;
    bool m_IsStart;
    int m_Width, m_Height;
    std::vector<std::vector<MazeCell *>> m_Cells;
    SFENG::Transform *m_Transform;
    std::stack<MazeCell *> m_GeneratedCells;
    std::mt19937 randomGen;
    std::uniform_int_distribution<int> *dist;
    MazeCell *m_CurrentCell;
};