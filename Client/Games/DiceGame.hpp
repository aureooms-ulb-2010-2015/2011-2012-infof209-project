#ifndef DEF_DICEGAME
#define DEF_DICEGAME

#include "Game.hpp"
#include "../GameServer.hpp"

class DiceGame : public Game{

private:
	int _dice;

public:
	DiceGame(GameServer*, unsigned int, Board*);
	virtual ~DiceGame() = 0;
	virtual int rollDice();
	virtual int getDice();
    virtual void setDice(int);
};
#endif
