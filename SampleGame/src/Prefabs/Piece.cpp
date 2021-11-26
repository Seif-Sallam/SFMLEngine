#include "Prefabs/Piece.h"
sf::IntRect Piece::m_Textures[(uint32_t)PieceType::Type_Count] = {
	{},
	{},
	{},
	{},
	{},
	{},
	{},
	{},
	{},
	{},
	{},
	{},
};

Piece::Piece(SFENG::Entity* createdEntity, PieceType type, uint32_t row, uint32_t column)
	: entity(createdEntity), m_ArrayPosition(row, column), m_Type(type)
{
}

Piece::Piece(SFENG::Entity* createdEntity, PieceType type, Vec2u position)
	: entity(createdEntity), m_ArrayPosition(position), m_Type(type)
{
}
