#include "BackgammonPiece.hpp"


const string BackgammonPiece::RED_LETTER = "R";
const string BackgammonPiece::BLACK_LETTER = "B";
const string BackgammonPiece::RED_SYMBOL = "\033[1;31mR\033[0m";
const string BackgammonPiece::BLACK_SYMBOL = "N";

BackgammonPiece::BackgammonPiece(string letter, string color) : Piece(color),_letter(letter){
}

BackgammonRedPiece::BackgammonRedPiece() : BackgammonPiece(BackgammonPiece::RED_LETTER,BackgammonPiece::RED_SYMBOL){
	
}

BackgammonBlackPiece::BackgammonBlackPiece() : BackgammonPiece(BackgammonPiece::BLACK_LETTER,BackgammonPiece::BLACK_SYMBOL){

}

ostream& operator<<(ostream &out, Piece &currentPiece){
	out<< currentPiece.getColour() << endl;
	return out;
}
