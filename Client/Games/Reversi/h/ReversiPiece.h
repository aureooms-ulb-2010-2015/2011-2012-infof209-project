#if !defined(_REVERSIPIECE_H)
#define _REVERSIPIECE_H

#include <string>
#include "TrinaryState.h"
#include "../../Piece.hpp"

using namespace std;

class ReversiPiece:public Piece {
private:
	static string __BLACK;
	static string __WHITE;
	static string __UNSET;
	TrinaryState* __state;
	
public:
	ReversiPiece();
	virtual ~ReversiPiece();
	virtual bool black();
	virtual bool white();
	virtual bool not_set();
	virtual ReversiPiece& reverse();
	virtual ReversiPiece& setBlack();
	virtual ReversiPiece& setWhite();
	virtual ReversiPiece& unset();
	virtual ReversiPiece& init();
	virtual string toString();
};

#endif  //_REVERSIPIECE_H
