#include "Prefabs/Board.h"

Board::Board()
{
	////Place the pawns
	//for (int32_t i = 0; i < 8; i++)
	//{
	//	m_BoardPieces[6][i] = new Piece(PieceType::WhitePawn, 6, i);
	//	m_BoardPieces[1][i] = new Piece(PieceType::BlackPawn, 1, i);
	//}
	////Place the castles
	//m_BoardPieces[0][0] = new Piece(PieceType::WhiteCastle, 0, 0);
	//m_BoardPieces[0][7] = new Piece(PieceType::WhiteCastle, 0, 7);
	//m_BoardPieces[7][0] = new Piece(PieceType::BlackCastle, 7, 0);
	//m_BoardPieces[7][7] = new Piece(PieceType::BlackCastle, 7, 7);

	////Place the Bishops
	//m_BoardPieces[0][1] = new Piece(PieceType::WhiteKnight, 0, 1);
	//m_BoardPieces[0][6] = new Piece(PieceType::WhiteKnight, 0, 6);
	//m_BoardPieces[7][1] = new Piece(PieceType::BlackKnight, 7, 1);
	//m_BoardPieces[7][6] = new Piece(PieceType::BlackKnight, 7, 6);

	////Place the Knights
	//m_BoardPieces[0][2] = new Piece(PieceType::WhiteBishop, 0, 2);
	//m_BoardPieces[0][5] = new Piece(PieceType::WhiteBishop, 0, 5);
	//m_BoardPieces[7][2] = new Piece(PieceType::BlackBishop, 7, 2);
	//m_BoardPieces[7][5] = new Piece(PieceType::BlackBishop, 7, 5);

	////Place the Queens and Kings

	//m_BoardPieces[0][4] = new Piece(PieceType::WhiteKing, 0, 4);
	//m_BoardPieces[7][4] = new Piece(PieceType::BlackKing, 7, 4);
	//m_BoardPieces[0][3] = new Piece(PieceType::WhiteQueen, 0, 3);
	//m_BoardPieces[7][3] = new Piece(PieceType::BlackQueen, 7, 3);
}

Piece* Board::GetPieceAtPos(Vec2i position)
{
	if (position.x >= 0 && position.x < 8 && position.y >= 0 && position.y < 8)
		return m_BoardPieces[position.x][position.y];
	else
		return nullptr;
}

