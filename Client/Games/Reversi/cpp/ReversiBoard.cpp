#include "../h/ReversiBoard.h"

#include <iostream>
#include <sstream>

string ReversiBoard::__SPACE = " ";
string ReversiBoard::__EMPTY = "_";

ReversiBoard::ReversiBoard() : Board(8,8) {
	this->init();
}

void ReversiBoard::init() {
	for (unsigned short int i=0; i<8; i++){
		for (unsigned short int j=0; j<8; j++){
			this->_board[i][j] = NULL;
		}
	}

	cout << "Plateau initialisé" << endl;
	
	

}

void ReversiBoard::reset() {
	for (unsigned short int i=0; i<8; i++){
		for (unsigned short int j=0; j<8; j++){
			if (this->_board[i][j] != NULL){
				delete this->_board[i][j];
			}
		}
	}
	cout << "Plateau nettoyé" << endl;
	this->init();
	

}

bool ReversiBoard::validBox(unsigned short int column, unsigned short int row, ReversiPlayer* player) {
	unsigned short int j = column;
	unsigned short int i = row;
	if ( (i > 7 || i < 0) || ( j > 7 || j < 0) ) {return false;}
	else if (this->_board[i][j] != NULL)	{return false;}
	else{
		for (short int k = -1; k<2; k++){
			for (short int l = -1; l<2; l++){
				if ( k == 0 && l == 0)	{ continue;}
				else{
					bool waitingForBlack;
					bool waitingForClosingPiece = false;
					if (player->black()){
						waitingForBlack = false;
					}
					else{
						waitingForBlack = true;
					}
					for(unsigned short int m = 1; m < 8; m++){
						if (i+k*m > 7 || i+k*m < 0)	{break;}
						else if (j+l*m > 7 || j+l*m < 0)	{break;}
						else if (this->_board[i+k*m][j+l*m] == NULL)	{break;}
						if( (waitingForBlack && ((ReversiPiece*)(this->_board[i+k*m][j+l*m]))->black()) ||(!waitingForBlack && ((ReversiPiece*)(this->_board[i+k*m][j+l*m]))->white()) ){
							if (waitingForClosingPiece)	{return true;}
							else{
								waitingForClosingPiece = true;
								waitingForBlack = !waitingForBlack;
							}
						}
						else if ( !waitingForClosingPiece )	{break;}
					}
				}
			}
		}
		return false;
	}
}


void ReversiBoard::fillBox(unsigned short int column, unsigned short int row, ReversiPlayer* player, ReversiPiece* piece) {
	if (player->black()){
		piece->setBlack();
	}
	else if(player->white()){
		piece->setWhite();
	}
	this->addPiece(row,column,piece);
	cout << "avant update" << endl;
	this->updateAllDirections(column,row);
	cout << "après update" << endl;
	
}

string ReversiBoard::toString() {
	ostringstream result;
	result << "   0 1 2 3 4 5 6 7" << endl;
	for (unsigned short int i=0; i<8; i++){
		result << ReversiBoard::__SPACE;
		result << i;
		result << ReversiBoard::__SPACE;
		for (unsigned short int j=0; j<8; j++){
			if (this->_board[i][j] == NULL){
				result << ReversiBoard::__EMPTY;
			}
			else{
				result << ((ReversiPiece*)(this->_board[i][j]))->toString();
			}
			if (j<7){			
				result << ReversiBoard::__SPACE;
			}
		}
		if (i<7){
			result << endl;
		}
	}
	return result.str();
}

void ReversiBoard::display() {
	cout << this->toString() << endl;
}

bool ReversiBoard::noValidBox(ReversiPlayer* player) {
	for (unsigned short int i=0; i<8; i++){
		for (unsigned short int j=0; j<8; j++){
			if(this->validBox(i,j,player)){
				return false;
			}
		}
	}
	return true;

}

void ReversiBoard::updateAllDirections(unsigned short int column, unsigned short int row) {
	cout << "update" << endl;
	unsigned short int j = column;
	unsigned short int i = row;
	if (this->_board[i][j] != NULL){
		for (short int k = -1; k<2; k++){
			for (short int l = -1; l<2; l++){
				if ( k == 0 && l == 0)	{ continue;}
				else{
					this->updateDirection(column,row,HorizontalDirection(k),VerticalDirection(l));
				}
			}
		}
	}
	
}

void ReversiBoard::updateDirection(unsigned short int column, unsigned short int row, HorizontalDirection x, VerticalDirection y) {
	unsigned short int j = column;
	unsigned short int i = row;
	short int k = x.toInt();
	short int l = y.toInt();
	
	bool waitingForBlack;
	bool waitingForClosingPiece = false;
	if (((ReversiPiece*)(this->_board[i][j]))->black()){
		waitingForBlack = false;
	}
	else{
		waitingForBlack = true;
	}
	for(unsigned short int m = 1; m < 8; m++){
		if (i+k*m > 7 || i+k*m < 0)	{break;}
		else if (j+l*m > 7 || j+l*m < 0)	{break;}
		else if (this->_board[i+k*m][j+l*m] == NULL)	{break;}
		if( (waitingForBlack && ((ReversiPiece*)(this->_board[i+k*m][j+l*m]))->black()) ||(!waitingForBlack && ((ReversiPiece*)(this->_board[i+k*m][j+l*m]))->white()) ){
			if (waitingForClosingPiece)	{
				for(unsigned short int n = 1; n < m; n++){
					((ReversiPiece*)(this->_board[i+k*n][j+l*n]))->reverse();
				}
				break;
			}
			else{
				waitingForClosingPiece = true;
				waitingForBlack = !waitingForBlack;
			}
		}
		else if ( !waitingForClosingPiece )	{break;}
	}
	
}

unsigned short int ReversiBoard::blackCount(){
	unsigned short int count = 0;
	for (unsigned short int i=0; i<8; i++){
		for (unsigned short int j=0; j<8; j++){
			if(this->_board[i][j] != NULL && ((ReversiPiece*)(this->_board[i][j]))->black() ){
				count++;
			}
		}
	}
	return count;
}


unsigned short int ReversiBoard::whiteCount(){
	unsigned short int count = 0;
	for (unsigned short int i=0; i<8; i++){
		for (unsigned short int j=0; j<8; j++){
			if(this->_board[i][j] != NULL && ((ReversiPiece*)(this->_board[i][j]))->white() ){
				count++;
			}
		}
	}
	return count;
}
