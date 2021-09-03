#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <algorithm>
#include <math.h>
#include <fstream>
#include "SFML/Graphics.hpp"
#include "Vec2.h"
#include "ResourceManager.h"
//Needs refactoring
namespace SFENG {
	class Tilemap
	{
	public:
		Tilemap(const Vec2i& size, const Vec2f& startPos, const Vec2f& tileSize, const std::string& spriteSheet, sf::RenderWindow& window);
		void ReadMap(const std::string& map);
		void Darw();
		~Tilemap();
	private:
		sf::IntRect GetViewBoundries();
		Vec2i GetStartIndex(const sf::IntRect& viewBoundries);
		Vec2i GetEndIndex(const sf::IntRect& viewBoundries);
		sf::RectangleShape m_Tile;
		Vec2i m_Size;
		Vec2f m_StartPos;
		Vec2f m_TileSize;
		Vec2f m_ViewLimit;
		sf::RenderWindow& m_Window;
		sf::View m_View;
		sf::Texture* m_SheetTexture;
		Vec2<uint8_t>* m_MapIndicies;
		bool m_ErrorReading;
	};
}