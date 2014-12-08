#include "./GamePlayer.hpp"

GamePlayer::GamePlayer(string name):_name(name){
}

string GamePlayer::toString(){
	return this->_name;
}
