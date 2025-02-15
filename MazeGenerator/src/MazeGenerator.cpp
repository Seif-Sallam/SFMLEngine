#include "MazeGenerator.h"

MazeGenerator::MazeGenerator()
{
    m_Width = 10;
    m_Height = 10;
    startX = 0;
    startY = 0;
    dist = new std::uniform_int_distribution<int>(0, 4);
    m_Running = false;
    m_IsStart = true;
    m_Cells.resize(m_Width);
    for (int i = 0; i < m_Width; i++)
    {
        m_Cells[i].resize(m_Height);
        for (int j = 0; j < m_Height; j++)
        {
            m_Cells[i][j] = new MazeCell(SFENG::LCM::InstantiateObject("CellZ#" + std::to_string(i * m_Width + j)),
                                         i, j);
            m_Cells[i][j]->SetVisited(false);
            m_Cells[i][j]->SetState(CellState::NormalCell);
        }
    }
    m_CurrentCell = m_Cells[0][0];
    randomGen.seed(time(0));
}

MazeGenerator::~MazeGenerator()
{
    delete dist;
    for (int i = 0; i < m_Width; i++)
    {
        for (int j = 0; j < m_Height; j++)
        {
            delete m_Cells[i][j];
        }
        m_Cells[i].clear();
    }
    m_Cells.clear();
}

bool MazeGenerator::Init()
{
    m_Transform = &this->entity->GetComponent<SFENG::Transform>();

    return this->Component::Init();
}

void MazeGenerator::Draw(sf::RenderWindow &window)
{
}

void MazeGenerator::TakeStep()
{
    if (m_Running)
    {
        if (m_IsStart)
        {
            m_GeneratedCells.push(m_Cells[startX][startY]);
            m_Cells[startX][startY]->SetState(CellState::StartCell);
            m_CurrentCell = m_Cells[startX][startY];
            m_IsStart = false;
        }
        if (m_GeneratedCells.empty())
        {
            m_Running = false;
            return;
        }
        m_CurrentCell->SetState(CellState::NormalCell);
        m_CurrentCell = m_GeneratedCells.top();
        m_CurrentCell->SetVisited(true);
        m_CurrentCell->SetState(CellState::CurrentCell);
        lastX = m_CurrentCell->GetX();
        lastY = m_CurrentCell->GetY();
        std::vector<Direction> freeCells = GetFreeCells(m_CurrentCell->GetX(), m_CurrentCell->GetY());
        if (freeCells.size() == 0)
        {
            m_GeneratedCells.pop();
        }
        else
        {
            Direction dir = freeCells[(*dist)(randomGen) % freeCells.size()];
            int cellX = m_CurrentCell->GetX();
            int cellY = m_CurrentCell->GetY();

            Vec2i dirs[] = {{cellX, cellY - 1},
                            {cellX, cellY + 1},
                            {cellX + 1, cellY},
                            {cellX - 1, cellY}};

            m_CurrentCell->GetWalls()[dir] = false;
            auto &nextCell = m_Cells[dirs[(int)dir].x][dirs[int(dir)].y];
            bool *&walls = nextCell->GetWalls();
            if (dir == UP)
                walls[DOWN] = false;
            else if (dir == DOWN)
                walls[UP] = false;
            else if (dir == RIGHT)
                walls[LEFT] = false;
            else if (dir == LEFT)
                walls[RIGHT] = false;

            m_GeneratedCells.push(nextCell);
        }
    }
}

void MazeGenerator::DrawCell(sf::RenderWindow &window, int i, int j, sf::RectangleShape &shape, sf::RectangleShape borders[4])
{
    //Drawing using the direct SFML code is actually bad for large scale programs, it is better to use the
    // entity drawing mechanisims in the engine for much more increase of performance
    // const Vec2f offset = m_Transform->position;
    // borders[UP].setPosition(offset.x + i * 32.0f, offset.y + j * 32.0f);
    // borders[DOWN].setPosition(offset.x + i * 32.0f, offset.y + j * 32.0f + 32.0f);
    // borders[RIGHT].setPosition(offset.x + i * 32.0f + 32.0f, offset.y + j * 32.0f);
    // borders[LEFT].setPosition(offset.x + i * 32.0f, offset.y + j * 32.0f);
    // if (i == 0)
    //     borders[LEFT].move(sf::Vector2f(0.0f, -1.0f));

    // if (j == 0)
    //     borders[UP].move(sf::Vector2f(-1.0f, 0.f));
    // shape.setPosition(offset.x + i * 32.0f, offset.y + j * 32.0f);
    // if (m_Cells[i][j]->IsVisited())
    //     shape.setFillColor(sf::Color::White);
    // else
    //     shape.setFillColor(sf::Color::Red);

    // if (i == startX && j == startY)
    //     shape.setFillColor(sf::Color::Green);

    // if (i == lastX && j == lastY)
    //     shape.setFillColor(sf::Color::Yellow);

    // window.draw(shape);
    // bool *walls = m_Cells[i][j]->GetWalls();
    // for (int k = 0; k < 4; k++)
    // {
    //     if (walls[k] == true)
    //         borders[k].setFillColor(sf::Color::Blue);
    //     else
    //         borders[k].setFillColor(sf::Color::White);
    //     window.draw(borders[k]);
    // }
}

std::vector<Direction> MazeGenerator::GetFreeCells(int cellX, int cellY)
{
    std::vector<Direction> out;
    out.reserve(4);

    Vec2i dirs[] = {{cellX, cellY - 1},
                    {cellX, cellY + 1},
                    {cellX + 1, cellY},
                    {cellX - 1, cellY}};
    for (int i = 0; i < 4; i++)
    {
        if (dirs[i].x < m_Width && dirs[i].x > -1 && dirs[i].y < m_Height && dirs[i].y > -1)
            if (!m_Cells[dirs[i].x][dirs[i].y]->IsVisited())
                out.push_back((Direction)i);
    }
    return out;
}

void MazeGenerator::Reset()
{
    while (!m_GeneratedCells.empty())
        m_GeneratedCells.pop();
    m_IsStart = true;
    for (int i = 0; i < m_Cells.size(); i++)
    {
        for (int j = 0; j < m_Cells[i].size(); j++)
        {
            delete m_Cells[i][j];
        }
        m_Cells[i].clear();
    }
    m_Cells.clear();
    m_Cells.resize(m_Width);
    for (int i = 0; i < m_Width; i++)
    {
        m_Cells[i].resize(m_Height);
        for (int j = 0; j < m_Height; j++)
        {
            m_Cells[i][j] = new MazeCell(SFENG::LCM::InstantiateObject("Cell#" + std::to_string(i * m_Width + j)), i, j);
            m_Cells[i][j]->SetVisited(false);
            m_Cells[i][j]->SetState(CellState::NormalCell);
        }
    }
    m_Cells[startX][startY]->SetState(CellState::StartCell);
    m_CurrentCell = m_Cells[startX][startY];
}

void MazeGenerator::ImGuiLayer()
{
}

int MazeGenerator::GetWidth()
{
    return m_Width;
}

int MazeGenerator::GetHeight()
{
    return m_Height;
}

bool MazeGenerator::IsRunning()
{
    return m_Running;
}

void MazeGenerator::Run(bool v)
{
    m_Running = v;
}

void MazeGenerator::SetWidthAndHeight(int width, int height)
{
    this->m_Width = width;
    this->m_Height = height;
    Reset();
}

void MazeGenerator::SetOffset(const Vec2f &offset)
{
    for (int i = 0; i < m_Width; i++)
    {
        for (int j = 0; j < m_Height; j++)
        {
            m_Cells[i][j]->SetOffset(offset);
        }
    }
}

MazeCell *MazeGenerator::GetCurrentCell()
{
    return m_CurrentCell;
}