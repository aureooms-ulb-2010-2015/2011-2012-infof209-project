
#ifndef _BACKGAMMONPIECE_HPP
#define _BACKGAMMONPIECE_HPP

#include "../Piece.hpp"
#include <string>
#include <iostream>
using namespace std;

class BackgammonPiece : public Piece{
private:
	string _letter;

public:
	static const string RED_LETTER;
	static const string BLACK_LETTER;
	static const string RED_SYMBOL;
	static const string BLACK_SYMBOL;
	
	BackgammonPiece(string,string);

	virtual string letter(){return this->_letter;}
};

class BackgammonRedPiece : public BackgammonPiece{
public:
	BackgammonRedPiece();
	void display(){};
};


class BackgammonBlackPiece : public BackgammonPiece{
public:
	BackgammonBlackPiece();
	void display(){};
};


#endif
