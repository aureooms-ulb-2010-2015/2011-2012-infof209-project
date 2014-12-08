
#include "BackgammonBoard.hpp"
#include "BackgammonPiece.hpp"

#include <sstream>

BackgammonBoard::BackgammonBoard() : Board(24,15){
	
	this->eatenPieces[0] = 0;
	this->eatenPieces[1] = 0;
	this->exitedPieces[0] = 0;
	this->exitedPieces[1] = 0;
    
	for(int point = 0 ; point < 2 ; point++) { _board[0][point] = new BackgammonRedPiece(); }
	for(int point = 0 ; point < 5 ; point++) { _board[5][point] = new BackgammonBlackPiece(); }
	for(int point = 0 ; point < 3 ; point++) { _board[7][point] = new BackgammonBlackPiece(); }
	for(int point = 0 ; point < 5 ; point++) { _board[11][point] = new BackgammonRedPiece(); }
	for(int point = 0 ; point < 5 ; point++) { _board[12][point] = new BackgammonBlackPiece(); }
	for(int point = 0 ; point < 3 ; point++) { _board[16][point] = new BackgammonRedPiece(); }
	for(int point = 0 ; point < 5 ; point++) { _board[18][point] = new BackgammonRedPiece(); }
	for(int point = 0 ; point < 2 ; point++) { _board[23][point] = new BackgammonBlackPiece(); }

}

int BackgammonBoard::getEatenPieces(int index){
	return this->eatenPieces[index];
	
}

void BackgammonBoard::setEatenPieces(int index,int delta){
	this->eatenPieces[index] = this->eatenPieces[index] + delta;

}

int BackgammonBoard::getExitedPieces(int index){
	return this->exitedPieces[index];

}

void BackgammonBoard::setExitedPieces(int index, int delta){
	this->exitedPieces[index] = this->exitedPieces[index] + delta;
	
}

void BackgammonBoard::display(){
	cout << endl;
	cout << " ";
	for( int i = 13 ; i < 25 ; i++) {
		cout << i << "   " ;
	}
	cout << "    Prison :"<< endl;

	cout << " ";
	for( int j = 12 ; j < 24 ; j++) {
		cout << this->getContent(j) << "   ";
	}
	cout << "         " << this->getEatenPieces(0) << "\033[1;31mR\033[0m" << "  " << this->getEatenPieces(1) << "N";

	cout << endl<<endl<<endl;

	cout << " ";
	for( int k = 11 ; k > -1 ; k--) { cout << this->getContent(k) << "   ";}
	cout << "    Pièces sorties :"<< endl;

	cout << " ";
	for (int l = 12 ; l > 9 ; l-- ) { cout << l << "   " ; }
	for (int l = 9 ; l > 0 ; l-- ) { cout << l << "    " ; }

	cout << "         " << this->getExitedPieces(0) << "\033[1;31mR\033[0m" << "  " << this->getExitedPieces(1) << "N";
	cout << endl;
}


unsigned int BackgammonBoard::getNumberOfPieces(int point){
	unsigned int n = 0;
	while( this->getPieceInCell(point,n) != NULL){
		n++;
	}
	return n;
}


string BackgammonBoard::getColor(int point){
	if (this->getPieceInCell(point,0) == NULL){
		return "E";
	}
	return this->getPieceInCell(point,0)->getColour();
}

string BackgammonBoard::getContent(int point){
	
	if (this->getNumberOfPieces(point) > 0){
		ostringstream temp;
		temp << this->getNumberOfPieces(point) << this->getColor(point);
		return temp.str();
	}
	else{
		return "  ";
	}
}
