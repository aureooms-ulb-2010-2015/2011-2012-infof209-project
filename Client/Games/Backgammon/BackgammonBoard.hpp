
#ifndef _BACKGAMMONBOARD_HPP
#define _BACKGAMMONBOARD_HPP

#include "../Board.hpp"

class BackgammonBoard : public Board{

private:
	int eatenPieces[2];  // [0] will contain the number of Red eaten pieces, [1] the Black ones.
	int exitedPieces[2]; // Same as above but for exited pieces.
	
public:
	BackgammonBoard();
	int getEatenPieces(int);
	void setEatenPieces(int index,int incOrDec);
	int getExitedPieces(int index);
	void setExitedPieces(int index,int incOrDec);

	virtual string getContent(int);
	virtual unsigned int getNumberOfPieces(int);
	virtual string getColor(int);

	virtual void display();

};

#endif
