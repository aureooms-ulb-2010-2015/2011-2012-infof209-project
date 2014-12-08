#include "CheckersPlayer.hpp"

using namespace std;

CheckersPlayer::CheckersPlayer(string colour) : GamePlayer(colour),  _colour(colour),_isMyTurn(false)
{

}
CheckersPlayer::~CheckersPlayer()
{

}

string CheckersPlayer::getColour()
{
    return this->_colour;
}

bool CheckersPlayer::isMyTurn()
{
    return this->_isMyTurn;
}

void CheckersPlayer::switchTurn()
{
    if (this->_isMyTurn)
        this->_isMyTurn = false;
    else
        this->_isMyTurn = true;
}

