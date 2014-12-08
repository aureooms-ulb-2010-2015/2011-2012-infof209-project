#include <iostream>
#include <string>
#include <sstream>

#include "LudoPlayer.hpp"
#include "LudoPiece.hpp"

using namespace std;

LudoPlayer::LudoPlayer(string color) : GamePlayer(color){
	_hisPieces = new vector<LudoPiece*>;
	
}

LudoPlayer::LudoPlayer(string color, int id) : GamePlayer(color){
	_hisPieces = new vector<LudoPiece*>;
	int intcolor;
	for(int i = 0; i<4; ++i){
		LudoPiece* newPiece= new LudoPiece(color,i);
		_hisPieces->push_back(newPiece);
		
	}
	this->setIDPlayer(id);
	istringstream temp(color);
	temp>>intcolor;
	this->setplayerColor(intcolor);
}

void LudoPlayer::showPiecesPosition(){
	for(int i=0;i<4;i++){
		cout<<_hisPieces->at(i)->getNumber()<<" en position "<<_hisPieces->at(i)->getPosition()<<endl;
	}
}

int LudoPlayer::makePosSum(){
	int res=0;
	for(int i=0; i<4;++i){res+=getPiece(i)->getPosition();}
	return res;
}

LudoPlayer::~LudoPlayer(){
	for(int i = 0; i<4; i++){
		delete(_hisPieces->at(i));
	}

	delete(_hisPieces);
}

//GETTERS SETTERS

void LudoPlayer::setplayerColor(int color){_playerColor=color;}

void LudoPlayer::setIDPlayer(int id){_idPlayer=id;}

int LudoPlayer::getIDPlayer(){return _idPlayer;}

int LudoPlayer::getPlayerColor(){return _playerColor;}

LudoPiece* LudoPlayer::getPiece(int i){return this->_hisPieces->at(i);}

vector<LudoPiece*>* LudoPlayer::getHisPieces(){return _hisPieces;}




