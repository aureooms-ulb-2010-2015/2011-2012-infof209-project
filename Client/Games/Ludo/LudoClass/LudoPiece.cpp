#include <iostream>
#include <string>
#include <sstream>

#include "LudoPiece.hpp"


using namespace std;

LudoPiece::LudoPiece(string color, int number) : Piece(color){
	
	int intcolor;
	istringstream temp(color);
	temp>>intcolor;
	this->setPieceColor(intcolor);
	
	
	this->setPosition(-1);
	this->setNumber(number);
	
	
	
	
}




//GETTERS SETTERS

void LudoPiece::setPosition(int position){_position=position;}
void LudoPiece::setPieceColor(int color){_pieceColor=color;}
void LudoPiece::setNumber(int number){_number=number;}

int LudoPiece::getPosition(){return _position;}
int LudoPiece::getPieceColor(){return _pieceColor;}
int LudoPiece::getNumber(){return _number;}


