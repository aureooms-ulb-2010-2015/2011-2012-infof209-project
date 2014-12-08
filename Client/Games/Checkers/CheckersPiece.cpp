#include "CheckersPiece.hpp"

#include <cmath>
#include <iostream>

using namespace std;

CheckersPiece::CheckersPiece(string colour): Piece(colour)
{

}
CheckersPiece::~CheckersPiece()
{

}

bool CheckersPiece::ownToPlayer(CheckersPlayer* player)
{
    return player->getColour() == this->_colour;
}
bool CheckersPiece::isValidMovement(int rowi,int columni,int rowf,int columnf)
{
	cout<<"Error"<<endl;
}

void CheckersPiece::display()
{

}

string CheckersPiece::getColour()
{
    return this->_colour;
}



StandardCheckersPiece::StandardCheckersPiece(string colour):CheckersPiece(colour)
{

}
StandardCheckersPiece::~StandardCheckersPiece()
{

}

void StandardCheckersPiece::display()
{
    if(this->_colour == "White")
        cout<<"O|";
    else if (this->_colour == "Black")
        cout<<"0|";
}

bool StandardCheckersPiece::isValidMovement(int rowi,int columni,int rowf,int columnf)
{
	cout<<"Validating movement for StandPiece"<<endl;
    if ((this->_colour == "Black" && rowf>rowi) || (this->_colour == "White" && rowf<rowi))
        return true;
    return false;

}

KingCheckersPiece::KingCheckersPiece(string colour):CheckersPiece(colour)
{

}
KingCheckersPiece::~KingCheckersPiece()
{

}
bool KingCheckersPiece::isValidMovement(int rowi,int columni,int rowf,int columnf)
{
	cout<<"Validating movement for KingPiece"<<endl;
    return fabs(columnf-columni) == fabs(rowf-rowi);
}

void KingCheckersPiece::display()
{
    if(this->_colour == "White")
        cout<<"1|";
    else if (this->_colour == "Black")
        cout<<"2|";
}
