#pragma once
#include "PCH.h"
enum class PieceType {
	BlackCastle,
	BlackKnight,
	BlackBishop,
	BlackQueen,
	BlackKing,
	BlackPawn,
	WhiteCastle,
	WhiteKnight,
	WhiteBishop,
	WhiteQueen,
	WhiteKing,
	WhitePawn,
	Type_Count
};

class Piece
{
public:
	Piece(SFENG::Entity* createdEntity, PieceType type, uint32_t row, uint32_t column);
	Piece(SFENG::Entity* createdEntity, PieceType type, Vec2u position);

	inline PieceType GetType() { return m_Type; }

	SFENG::Entity* entity;
private:
	Vec2u m_ArrayPosition;
	PieceType m_Type;
	static sf::IntRect m_Textures[(uint32_t)PieceType::Type_Count];
};