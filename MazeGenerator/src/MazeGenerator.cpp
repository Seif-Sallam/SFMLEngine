#include "../headers/MazeGenerator.h"

MazeGenerator::MazeGenerator()
{
    m_Width = 10;
    m_Height = 10;
    dist = new std::uniform_int_distribution<int>(0, 4);
    m_Running = false;
    m_IsStart = true;
    m_Cells.resize(m_Width);

    for (int i = 0; i < m_Width; i++)
    {
        m_Cells[i].resize(m_Height);
        for (int j = 0; j < m_Height; j++)
        {
            m_Cells[i][j].x = i;
            m_Cells[i][j].y = j;
        }
    }

    randomGen.seed(time(0));
}

MazeGenerator::~MazeGenerator()
{
    delete dist;
}

bool MazeGenerator::Init()
{
    m_Transform = &this->entity->GetComponent<SFENG::Transform>();

    return this->Component::Init();
}

void MazeGenerator::Draw(sf::RenderWindow &window)
{
    sf::RectangleShape borders[4];
    borders[FRONT].setSize(sf::Vector2f(32.f, 2.0f));
    borders[BACK].setSize(sf::Vector2f(32.f, 2.0f));
    borders[RIGHT].setSize(sf::Vector2f(2.0f, 32.f));
    borders[LEFT].setSize(sf::Vector2f(2.0f, 32.f));
    sf::RectangleShape BOX(sf::Vector2f(32.0f, 32.0f));
    for (int i = 0; i < m_Width; i++)
    {
        for (int j = 0; j < m_Height; j++)
        {
            DrawCell(window, i, j, BOX, borders);
        }
    }
}

void MazeGenerator::TakeStep()
{
    if (m_Running)
    {
        if (m_IsStart)
        {
            m_GeneratedCells.push(&m_Cells[startX][startY]);
            m_IsStart = false;
        }
        if (m_GeneratedCells.empty())
        {
            m_Running = false;
            return;
        }
        MazeCell *currentCell = m_GeneratedCells.top();
        currentCell->visited = true;
        lastX = currentCell->x;
        lastY = currentCell->y;
        std::vector<Direction> freeCells = GetFreeCells(currentCell->x, currentCell->y);
        if (freeCells.size() == 0)
        {
            m_GeneratedCells.pop();
        }
        else
        {
            Direction dir = freeCells[(*dist)(randomGen) % freeCells.size()];
            int cellX = currentCell->x;
            int cellY = currentCell->y;

            Vec2i dirs[] = {{cellX, cellY - 1},
                            {cellX, cellY + 1},
                            {cellX + 1, cellY},
                            {cellX - 1, cellY}};

            currentCell->wall[dir] = false;
            auto &nextCell = m_Cells[dirs[(int)dir].x][dirs[int(dir)].y];
            if (dir == FRONT)
                nextCell.wall[BACK] = false;
            else if (dir == BACK)
                nextCell.wall[FRONT] = false;
            else if (dir == RIGHT)
                nextCell.wall[LEFT] = false;
            else if (dir == LEFT)
                nextCell.wall[RIGHT] = false;

            m_GeneratedCells.push(&nextCell);
        }
    }
}

void MazeGenerator::DrawCell(sf::RenderWindow &window, int i, int j, sf::RectangleShape &shape, sf::RectangleShape borders[4])
{
    //Drawing using the direct SFML code is actually bad for large scale programs, it is better to use the
    // entity drawing mechanisims in the engine for much more increase of performance
    const Vec2f offset = m_Transform->position;
    borders[FRONT].setPosition(offset.x + i * 32.0f, offset.y + j * 32.0f);
    borders[BACK].setPosition(offset.x + i * 32.0f, offset.y + j * 32.0f + 32.0f);
    borders[RIGHT].setPosition(offset.x + i * 32.0f + 32.0f, offset.y + j * 32.0f);
    borders[LEFT].setPosition(offset.x + i * 32.0f, offset.y + j * 32.0f);
    if (i == 0)
        borders[LEFT].move(sf::Vector2f(0.0f, -1.0f));

    if (j == 0)
        borders[FRONT].move(sf::Vector2f(-1.0f, 0.f));
    shape.setPosition(offset.x + i * 32.0f, offset.y + j * 32.0f);
    if (m_Cells[i][j].visited)
        shape.setFillColor(sf::Color::White);
    else
        shape.setFillColor(sf::Color::Red);

    if (i == startX && j == startY)
        shape.setFillColor(sf::Color::Green);

    if (i == lastX && j == lastY)
        shape.setFillColor(sf::Color::Yellow);

    window.draw(shape);
    for (int k = 0; k < 4; k++)
    {
        if (m_Cells[i][j].wall[k] == true)
            borders[k].setFillColor(sf::Color::Blue);
        else
            borders[k].setFillColor(sf::Color::White);
        window.draw(borders[k]);
    }
}

std::vector<MazeGenerator::Direction> MazeGenerator::GetFreeCells(int cellX, int cellY)
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
            if (!m_Cells[dirs[i].x][dirs[i].y].visited)
                out.push_back((Direction)i);
    }
    return out;
}

void MazeGenerator::SetWidth(int width)
{
    m_Width = width;
    Reset();
}

void MazeGenerator::SetHeight(int height)
{
    m_Height = height;
    Reset();
}

void MazeGenerator::Reset()
{
    while (!m_GeneratedCells.empty())
        m_GeneratedCells.pop();
    m_IsStart = true;
    m_Cells.clear();
    m_Cells.resize(m_Width);
    for (int i = 0; i < m_Width; i++)
    {
        m_Cells[i].resize(m_Height);
        for (int j = 0; j < m_Height; j++)
        {
            m_Cells[i][j].x = i;
            m_Cells[i][j].y = j;
        }
    }
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
