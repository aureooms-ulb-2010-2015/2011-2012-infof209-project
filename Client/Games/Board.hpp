#ifndef _BOARD_HPP
#define _BOARD_HPP

#include "Piece.hpp"
#include <iostream>
using namespace std;

class Board{
protected:
	Piece*** _board;
	
public:
	Board(int size_x,int size_y);
	virtual ~Board();
	Piece* getPieceInCell(int);
	Piece* getPieceInCell(int,int);
	virtual void addPiece(int,Piece*);
	virtual void addPiece(int,int,Piece*);
	virtual void removePiece(int);
	virtual void removePiece(int,int);
	virtual bool isEmpty(int,int);
	virtual void display()=0;
};

#endif
