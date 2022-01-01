#pragma once
#include "PCH.h"
#include <stack>
class MazeGenerator : public SFENG::Component
{
public:
    MazeGenerator();
    ~MazeGenerator() override;
    bool Init() override;
    void ImGuiLayer() override;
    void Draw(sf::RenderWindow &window) override;
    void SetWidth(int width);
    void SetHeight(int height);
    int GetWidth();
    int GetHeight();
    void Reset();
    bool IsRunning();
    void Run(bool v);
    int startX, startY;
    void TakeStep();

private:
    struct MazeCell
    {
        bool wall[4] = {true, true, true, true};
        int x, y;
        bool visited = false;
    };
    enum Direction
    {
        FRONT,
        BACK,
        RIGHT,
        LEFT
    };

    void DrawCell(sf::RenderWindow &window, int i, int j, sf::RectangleShape &shape, sf::RectangleShape borders[4]);
    std::vector<Direction> GetFreeCells(int i, int j);
    int lastX, lastY;
    bool m_Running;
    bool m_IsStart;
    int m_Width, m_Height;
    std::vector<std::vector<MazeCell>> m_Cells;
    SFENG::Transform *m_Transform;
    std::stack<MazeCell *> m_GeneratedCells;
    std::mt19937 randomGen;
    std::uniform_int_distribution<int> *dist;
};