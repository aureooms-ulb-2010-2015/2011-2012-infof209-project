#ifndef CHECKERSGAME_HPP_INCLUDED
#define CHECKERSGAME_HPP_INCLUDED

#include <iostream>
#include <vector>

#include "CheckersBoard.hpp"
#include "CheckersPlayer.hpp"
#include "../Game.hpp"
#include "../../GameServer.hpp"
#include "../../../Common/Request.hpp"

class CheckersGame : public Game{
protected:
	bool _hasCapture;

public:
	CheckersGame(GameServer* server);
	CheckersGame(GameServer* server,CheckersBoard* b);
	~CheckersGame();

	virtual void makeMove(int,int,int,int);
	virtual bool validateMovement(int,int,int,int,CheckersPlayer*);
	virtual bool isCapturePossible(CheckersPlayer*);
	virtual bool capturePossibilityForKingPiece(int,int,CheckersPiece*);
	virtual bool capturePossibilityForStandardPiece(int,int,CheckersPiece*);

	virtual CheckersBoard* c_board();
	virtual CheckersPlayer* c_player();

	virtual int winner();
	virtual bool endOfGame();
	virtual bool endOfTurn();
	virtual Move* parseMove(string);
	virtual void makeMove(Move*);
	virtual void runActiveTurn();


};


#endif // CHECKERSGAME_HPP_INCLUDED
