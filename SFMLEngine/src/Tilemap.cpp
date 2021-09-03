#include "../headers/Tilemap.h"

SFENG::Tilemap::Tilemap(const Vec2i& size, const Vec2f& startPos, const Vec2f& tileSize, const std::string& spriteSheet, sf::RenderWindow& window)
	: m_Size(size), m_StartPos(startPos), m_TileSize(tileSize), m_Window(window)
{
	m_SheetTexture = &SFENG::ResourceManager::GetTextrue(spriteSheet);
	m_MapIndicies = new Vec2<uint8_t>[m_Size.x * m_Size.y];
	m_ErrorReading = false;
	m_Tile.setPosition(m_StartPos);
	m_Tile.setSize(m_TileSize);
	m_Tile.setTexture(m_SheetTexture);
	m_ViewLimit = m_Size * m_TileSize + m_StartPos;
}

void SFENG::Tilemap::ReadMap(const std::string& map)
{
	//Openning it in binary format
	std::ifstream file(map, std::ios::binary);
	if (file.is_open())
	{
		for (int i = 0; i < m_Size.y; i++) // Rows
			for (int j = 0; j < m_Size.x; j++) // Columns
			{
				int32_t index = j + i * m_Size.x;
				if (index >= m_Size.x * m_Size.y)
				{
					std::cout << "Index out of bounds!!\n";
					m_ErrorReading = true;
					continue;
				}
				std::string str;
				file >> str;
				int in = str.find("_");
				uint8_t x = std::stoi(str.substr(0, in));
				uint8_t y = std::stoi(str.substr(in + 1));
				m_MapIndicies[index].x = x;
				m_MapIndicies[index].y = y;
			}
	}
	else
	{
		//Tile Map Was not opened F*ck!
		return;
	}
}

void SFENG::Tilemap::Darw()
{
	sf::IntRect rect{ 0, 0, (int)m_TileSize.x, (int)m_TileSize.y };
	const Vec2f& pos = m_StartPos;
	auto viewBoundries = GetViewBoundries();
	auto startIndicies = GetStartIndex(viewBoundries);
	auto endIndicies = GetEndIndex(viewBoundries);
	for (int j = startIndicies.y; j < endIndicies.y; j++) // Columns
		for (int i = startIndicies.x; i < endIndicies.x; i++) // Rows
		{
			uint32_t index = j + i * m_Size.x;
			Vec2f finalPos = { pos.x + j * m_TileSize.x, pos.y + i * m_TileSize.y };
			m_Tile.setPosition(finalPos);
			rect.left = m_MapIndicies[index].x * m_TileSize.x;
			rect.top = m_MapIndicies[index].y * m_TileSize.y;
			m_Tile.setTextureRect(rect);
			m_Window.draw(m_Tile);
		}
}

SFENG::Tilemap::~Tilemap()
{
	delete[] m_MapIndicies;
}

sf::IntRect SFENG::Tilemap::GetViewBoundries()
{
	auto& view = m_Window.getView();
	Vec2f viewHalf = view.getSize() / 2.0f;
	return sf::IntRect(view.getCenter().x - viewHalf.x, view.getCenter().y - viewHalf.y,
		view.getCenter().x + viewHalf.x, view.getCenter().y + viewHalf.y);
}

Vec2i SFENG::Tilemap::GetStartIndex(const sf::IntRect& viewBoundries)
{
	float check = ((float)viewBoundries.left - m_StartPos.x) / m_TileSize.x;
	int32_t startIndexC = (viewBoundries.left <= m_StartPos.x) ? 0 : (check >= m_Size.x) ? m_Size.x : (int32_t)check;
	check = (float)(viewBoundries.top - m_StartPos.y) / m_TileSize.y;
	int32_t startIndexR = (viewBoundries.top <= m_StartPos.y) ? 0 : (check >= m_Size.y) ? m_Size.y : (int32_t)check;

	return Vec2i(startIndexR, startIndexC);
}

Vec2i SFENG::Tilemap::GetEndIndex(const sf::IntRect& viewBoundries)
{
	float check = ((float)viewBoundries.width - m_StartPos.x) / m_TileSize.x;
	int32_t endIndexC = (viewBoundries.width <= m_StartPos.x) ? 0 : (viewBoundries.width >= m_ViewLimit.x) ? m_Size.x : (check <= 0.f) ? 0 : (int32_t)check + 1;
	check = (float)(viewBoundries.height - m_StartPos.y) / m_TileSize.y;
	int32_t endIndexR = (viewBoundries.height <= m_StartPos.y) ? 0 : (viewBoundries.height >= m_ViewLimit.y) ? m_Size.y : (check <= 0.f) ? 0 : (int32_t)check + 1;
	return Vec2i(endIndexR, endIndexC);
}