#if !defined(_REVERSIBOARD_H)
#define _REVERSIBOARD_H

#include <string>
#include "ReversiPlayer.h"
#include "ReversiPiece.h"
#include "HorizontalDirection.h"
#include "VerticalDirection.h"
#include "../../Board.hpp"

using namespace std;

class ReversiBoard : public Board{

private:
	static string __SPACE;
	static string __EMPTY;

	virtual void updateDirection(unsigned short int column, unsigned short int row, HorizontalDirection x, VerticalDirection y);
	virtual void updateAllDirections(unsigned short int column, unsigned short int row);
	
public:
	ReversiBoard();
	virtual void init();
	virtual void reset();
	virtual bool validBox(unsigned short int column, unsigned short int row, ReversiPlayer* player);
	virtual void fillBox(unsigned short int column, unsigned short int row, ReversiPlayer* player,ReversiPiece* piece);
	virtual string toString();
	virtual void display();
	virtual bool noValidBox(ReversiPlayer* player);
	virtual unsigned short int blackCount();
	virtual unsigned short int whiteCount();
};

#endif  //_REVERSIBOARD_H
