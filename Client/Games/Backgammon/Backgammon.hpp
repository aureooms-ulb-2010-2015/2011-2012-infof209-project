
#ifndef _BACKGAMMON_HPP
#define _BACKGAMMON_HPP

#include "BackgammonPiece.hpp"
#include "BackgammonBoard.hpp"
#include "BackgammonPlayer.hpp"


#include "../DiceGame.hpp"
#include "../../GameServer.hpp"
#include <string>
#include <iostream>

using namespace std;

class Backgammon : public DiceGame{
private:
	int currentDice[4];
	int CurrentPlayerID;

	
public:
	Backgammon(GameServer* server);
	~Backgammon();

	virtual string getPoint(int point);
	virtual string getPointColor(int point);

	virtual unsigned short int otherPlayerIndex();

	virtual void normalMove(int, int);
	virtual void moveFromEaten(int,string);
	virtual void exitMove(int);

	virtual bool mayExitPieces();
	virtual bool canExitPieces();
	virtual bool mustEnterPieces();
	virtual bool canEnterPieces();
	virtual bool canMakeNormalMove();
	virtual bool noPossibleMove();

	virtual string buildMove(int);

	virtual bool exists(int);
	virtual bool redPoint(int);
	virtual bool blackPoint(int);
	virtual bool emptyPoint(int);
	virtual bool owned(int);
	virtual bool ownedByOther(int);
	virtual bool catchable(int);
	virtual bool exitPoint(int);
	virtual bool enterPoint(int);

	virtual unsigned short int askPoint(string);
	virtual unsigned short int askFromPoint();
	virtual unsigned short int askToPoint();
	virtual unsigned short int askExitPoint();
	virtual unsigned short int askEnterPoint();

	virtual BackgammonPiece* topPiece(int);
	virtual BackgammonPiece* popPiece(int);
	virtual bool sameColor(int,int);
	virtual void movePiece(int,int);


	virtual bool diceLeft();
	virtual void displayDices();
	virtual void copyDices();
	virtual void rollDices();
	virtual void resetDices();
	virtual bool rolledDouble();
	virtual unsigned short int askDice();
	virtual bool wrongDiceChoice(unsigned short int);

	virtual BackgammonBoard* c_board();
	virtual BackgammonPlayer* c_player();

	virtual int winner();
	virtual bool endOfGame();
	virtual bool endOfTurn();
	virtual Move* parseMove(string);
	virtual void makeMove(Move*);
	virtual void runActiveTurn();
};


#endif
