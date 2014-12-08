#include "../h/Reversi.h"
#include "../h/ReversiBlackPlayer.h"
#include "../h/ReversiWhitePlayer.h"
#include "../h/ReversiMove.h"



#include <iostream>
#include <stdlib.h>
#include <limits>
#include <sstream>

const unsigned short int Reversi::__FIRST_PLAYER = 0;
const unsigned short int Reversi::__SECOND_PLAYER = 1;

//CONSTRUCTOR
Reversi::Reversi(GameServer* server): Game(server,2,new ReversiBoard()){
	this->init();
}


Reversi::Reversi(GameServer* server, ReversiBoard* board): Game(server,2,board){}


//GETTERS
ReversiBoard* Reversi::c_board() {
	return (ReversiBoard*) this->board();
}

stack<ReversiPiece*> Reversi::pieces() {
	return this->_pieces;
}

ReversiPlayer* Reversi::player(unsigned short int i) {
	return (ReversiPlayer*) (this->players()->at(i));
}



//SETTERS


//INIT
void Reversi::init() {

	for (unsigned short int i = 0; i<64; i++){
		this->_pieces.push(new ReversiPiece());
	}
	cout << "Pièces ajoutées" << endl;
	
	this->players()->push_back(new ReversiBlackPlayer());
	this->players()->push_back(new ReversiWhitePlayer());


	cout << "Joueurs ajoutées" << endl;

	this->c_board()->addPiece(3,3,&this->_pieces.top()->setBlack());
	this->_pieces.pop();
	this->c_board()->addPiece(3,4,&this->_pieces.top()->setWhite());
	this->_pieces.pop();
	this->c_board()->addPiece(4,3,&this->_pieces.top()->setWhite());
	this->_pieces.pop();
	this->c_board()->addPiece(4,4,&this->_pieces.top()->setBlack());
	this->_pieces.pop();

	cout << "Pièces centrales ajoutées" << endl;

	cout << "Jeu initialisé" << endl;
	

}

//PLAY (MAIN METHOD)

bool Reversi::cannotPlay(ReversiPlayer* player) {
	return this->c_board()->noValidBox(player);

}

bool Reversi::endOfGame() {
	return ( this->cannotPlay(this->player(0)) && this->cannotPlay(this->player(1)) );

}

void Reversi::fillBoardBox(unsigned short int column,unsigned short int row, ReversiPlayer* player){
	this->c_board()->fillBox(column,row,player,this->_pieces.top());
	this->_pieces.pop();
	
}

int Reversi::winner() {
	if (this->c_board()->blackCount() > this->c_board()->whiteCount()){
		return Reversi::__FIRST_PLAYER;
	}
	else if (this->c_board()->blackCount() < this->c_board()->whiteCount()){
		return Reversi::__SECOND_PLAYER;
	}
	else{
		return Game::NO_WINNER;
	}

}

unsigned short int Reversi::askColumn(){
	unsigned short int column = 8;
	*this->promptInput("Quelle colonne? ") >> column;
	return column;
}
unsigned short int Reversi::askRow(){
	unsigned short int row = 8;
	*this->promptInput("Quelle rangée? ") >> row;
	return row;
}


void Reversi::displayScore(){
	cout << "Le score est :" << endl;
	cout << "\t Cases noires : " << this->c_board()->blackCount() << endl;
	cout << "\t Cases blanches : " << this->c_board()->whiteCount() << endl;
}



//MESSAGES


Move* Reversi::parseMove(string data){
	return new ReversiMove(data);
}

void Reversi::makeMove(Move* move){
	ReversiMove* cast = (ReversiMove*)move;
	this->fillBoardBox(cast->column(),cast->row(),this->player(cast->player()));	
}



//NEW

void Reversi::runActiveTurn(){
	ReversiPlayer* player = (ReversiPlayer*)this->currentPlayer();

	cout<<"C'est votre tour."<<endl;

	if(this->cannotPlay(player)){
		this->promptPause("Il n'y a aucune case jouable dans votre couleur.  Appuyez sur ENTER.");
	}
	else{
		unsigned short int column;
		unsigned short int row;
		column = this->askColumn();
		row = this->askRow();
		while( true ){
			if(this->c_board()->validBox(column,row,player)){
				break;
			}
			else{	
				system("clear");
				this->displayTurn();
				cout << "La case entrée précédemment n'est pas jouable" << endl;
				column = this->askColumn();
				row = this->askRow();
			}
		}
		ReversiMove* move= new ReversiMove(column,row,this->id());
		this->handleMove(move);
	}
	
}
