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
#include "LifeCycleManager.h"
//Needs refactoring
namespace SFENG {
	class Transform;
	class SpriteRenderer;
	class Tilemap
	{
	public:
		Tilemap(const Vec2i& size, const Vec2f& startPos, const Vec2f& tileSize, const std::string& spriteSheet, LifeCycleManager* LCM);
		void ReadMap(const std::string& map);
		~Tilemap();
	private:
		void CleanUp();
		struct Tile
		{
			Entity* thisEn;
			Transform* trans;
			SpriteRenderer* sr;
		};
		
		Vec2i m_Size;
		Vec2f m_StartPos;
		Vec2f m_TileSize;
		LifeCycleManager* m_LCM;
		std::vector<Tile*> m_Tiles;
		static int32_t s_TileNum;
	};
}