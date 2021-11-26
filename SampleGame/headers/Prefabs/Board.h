#pragma once
#include "PCH.h"
#include "Piece.h"
class Board 
{
public:
	Board();
	Piece* GetPieceAtPos(Vec2i position);


	SFENG::Entity* entity;
private:
	Piece* m_BoardPieces[8][8];
};