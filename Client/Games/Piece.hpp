#ifndef _PIECE_HPP
#define _PIECE_HPP
#include <string>
using namespace std;

class Piece{
	
protected:
	string _colour;
	
public:
	Piece(string colourToSet);
	virtual ~Piece();
	virtual string getColour() {return _colour;}
	virtual void setColour(string colourToSet) { _colour = colourToSet;}
	virtual void display(){};
};

#endif
