#include "BackgammonPlayer.hpp"


const bool BackgammonPlayer::RED_COLOR = 0;
const bool BackgammonPlayer::BLACK_COLOR = 1;
const string BackgammonPlayer::RED_LETTER = "R";
const string BackgammonPlayer::BLACK_LETTER = "B";

BackgammonPlayer::BackgammonPlayer(string name,bool color,string letter,int exitValue,int startValue,int multiplier):GamePlayer(name),_color(color),_letter(letter),_exitValue(exitValue),_startValue(startValue),_multiplier(multiplier)
{}

bool BackgammonPlayer::red(){
	return this->color() == BackgammonPlayer::RED_COLOR;
}

bool BackgammonPlayer::black(){
	return this->color() == BackgammonPlayer::BLACK_COLOR;
}

BackgammonRedPlayer::BackgammonRedPlayer():BackgammonPlayer("Joueur rouge", BackgammonPlayer::RED_COLOR, BackgammonPlayer::RED_LETTER, 24,0,1){}


BackgammonBlackPlayer::BackgammonBlackPlayer():BackgammonPlayer("Joueur noir", BackgammonPlayer::BLACK_COLOR, BackgammonPlayer::BLACK_LETTER, -1,23,-1){}
