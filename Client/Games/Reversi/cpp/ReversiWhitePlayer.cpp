#include "../h/ReversiWhitePlayer.h"

string ReversiWhitePlayer::_NAME = "Joueur blanc";

ReversiWhitePlayer::ReversiWhitePlayer() : ReversiPlayer(ReversiPlayer::_WHITE){

}


string ReversiWhitePlayer::toString(){
	return ReversiWhitePlayer::_NAME;
}
