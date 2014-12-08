#include <cstdlib>
#include <cstdio>
#include <ctime>
#include "DiceGame.hpp"

DiceGame::DiceGame(GameServer* server, unsigned int numberOfPlayers, Board* board): Game(server, numberOfPlayers, board){

	this->setDice(-1);



}


DiceGame::~DiceGame(){}

int DiceGame::rollDice(){
	srand((rand()%9973)+time(NULL));
	srand(rand()%9973);
	srand(rand()+time(NULL));
	return (rand()%6)+1;
}

int DiceGame::getDice(){return _dice;}
void DiceGame::setDice(int dice){_dice=dice;}
