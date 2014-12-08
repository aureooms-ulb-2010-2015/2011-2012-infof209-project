#include "../h/ReversiBlackPlayer.h"

string ReversiBlackPlayer::_NAME = "Joueur noir";

ReversiBlackPlayer::ReversiBlackPlayer() : ReversiPlayer(ReversiPlayer::_BLACK){
}


string ReversiBlackPlayer::toString(){
	return ReversiBlackPlayer::_NAME;
}
