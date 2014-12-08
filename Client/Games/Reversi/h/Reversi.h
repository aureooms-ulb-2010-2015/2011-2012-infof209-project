#if !defined(_REVERSI_H)
#define _REVERSI_H

#include "ReversiBoard.h"


#include "ReversiPiece.h"
#include "ReversiPlayer.h"

#include "../../../GameServer.hpp"
#include "../../../../Common/Request.hpp"
#include "../../Game.hpp"

#include <stack>
#include <vector>

using namespace std;

class Reversi : public Game{
protected:
	static const unsigned short int __FIRST_PLAYER;
	static const unsigned short int __SECOND_PLAYER;
	stack<ReversiPiece*> _pieces;
	
	
	
public:
	Reversi(GameServer* server);
	Reversi(GameServer* server,ReversiBoard* board);
	virtual ReversiBoard* c_board();
	virtual stack<ReversiPiece*> pieces();
	virtual ReversiPlayer* player(unsigned short int);

	virtual void init();
	virtual bool cannotPlay(ReversiPlayer* player);
	virtual void fillBoardBox(unsigned short int,unsigned short int, ReversiPlayer*);
	
	virtual unsigned short int askColumn();
	virtual unsigned short int askRow();


	virtual int winner();
	virtual Move* parseMove(string);
	virtual void makeMove(Move*);
	virtual void runActiveTurn();
	virtual bool endOfGame();
	virtual void displayScore();
};

#endif  //_REVERSI_H
