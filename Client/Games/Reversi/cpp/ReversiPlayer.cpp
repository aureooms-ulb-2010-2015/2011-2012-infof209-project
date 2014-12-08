#include "../h/ReversiPlayer.h"

const bool ReversiPlayer::_BLACK = true;
const bool ReversiPlayer::_WHITE = false;

ReversiPlayer::ReversiPlayer(bool color):

GamePlayer(
	(color == ReversiPlayer::_BLACK)?"Joueur noir":"Joueur blanc"
),

_color(color){}


bool ReversiPlayer::black(){
	return this->_color == ReversiPlayer::_BLACK;
}

bool ReversiPlayer::white(){
	return this->_color == ReversiPlayer::_WHITE;
}
