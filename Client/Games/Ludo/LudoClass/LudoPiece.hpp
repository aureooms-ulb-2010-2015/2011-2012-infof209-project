#ifndef _PIECE_H_
#define _PIECE_H_



#include "../../Piece.hpp"

class LudoPiece : public Piece
{
	private:
		int _pieceColor;
		int _number;//nécessaire pour que le joueur distingue ses pieces, on peut luis dire "tu bouges la piece 2"
		int _position;
		
		
	public:
		
		LudoPiece(std::string color,int number);
		
		void setPosition(int position);
		void setPieceColor(int color);
		void setNumber(int number);
		
		int getPosition();
		int getPieceColor();
		int getNumber();
		void display(){};
};


#endif



