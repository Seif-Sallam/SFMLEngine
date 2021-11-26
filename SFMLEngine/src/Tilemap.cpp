#include "Tilemap.h"
#include "Components/SpriteRenderer.h"
int32_t SFENG::Tilemap::s_TileNum = 0;

SFENG::Tilemap::Tilemap(const Vec2i& size, const Vec2f& startPos, const Vec2f& tileSize, const std::string& spriteSheet, LifeCycleManager* LCM)
	: m_Size(size)
	, m_StartPos(startPos)
	, m_TileSize(tileSize)
	, m_LCM(LCM)
{
	for (int32_t i = 0; i < m_Size.x * m_Size.y; i++) 
	{
		Entity* en = m_LCM->CreateEntity("tile" + std::to_string(s_TileNum++));
		Tile* tile = new Tile;
		tile->thisEn = en;
		tile->sr = &en->AddComponent<SpriteRenderer>();
		tile->trans = &en->GetCopmonent<Transform>();
		tile->sr->AttachTexture(spriteSheet);
		m_Tiles.push_back(tile);
	}
}

void SFENG::Tilemap::ReadMap(const std::string& map)
{
	std::ifstream file(map);
	if (file.is_open())
	{
		sf::IntRect rect;
		rect.width = m_TileSize.x;
		rect.height = m_TileSize.y;
		for (int i = 0; i < m_Size.y; i++) // Rows
			for (int j = 0; j < m_Size.x; j++) // Columns
			{
				int32_t index = j + i * m_Size.x;
				std::string str;
				file >> str;
				int in = str.find("_");
				if (in != std::string::npos) {
					uint8_t x = std::stoi(str.substr(0, in));
					uint8_t y = std::stoi(str.substr(in + 1));
					m_Tiles[index]->trans->position = (Vec2f(m_StartPos.y + j * m_TileSize.x, m_StartPos.y + i * m_TileSize.y));
					rect.left = x * m_TileSize.x;
					rect.top = y * m_TileSize.y;
					m_Tiles[index]->sr->SetRect(rect);
				}
			}
	}
	else
	{
		CleanUp();
		m_Tiles.clear();
	}
}


SFENG::Tilemap::~Tilemap()
{
	CleanUp();
	m_Tiles.clear();
}

void SFENG::Tilemap::CleanUp()
{
	for (auto& tile : m_Tiles)
		tile->thisEn->Destory();
}