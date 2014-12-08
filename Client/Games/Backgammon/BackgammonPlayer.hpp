#ifndef _BACKGAMMONPLAYER_H
#define _BACKGAMMONPLAYER_H

#include "../GamePlayer.hpp"

class BackgammonPlayer:public GamePlayer{
private:
	bool _color;
	string _letter;
	int _exitValue;
	int _startValue;
	int _multiplier;
public:
	static const bool RED_COLOR;
	static const bool BLACK_COLOR;
	static const string RED_LETTER;
	static const string BLACK_LETTER;

	BackgammonPlayer(string,bool,string,int,int,int);

	bool color(){return this->_color;}
	string letter(){return this->_letter;}
	int exitValue(){return this->_exitValue;}
	int startValue(){return this->_startValue;}
	int multiplier(){return this->_multiplier;}

	bool red();
	bool black();

	
};


class BackgammonRedPlayer:public BackgammonPlayer{

public:
	BackgammonRedPlayer();
	
};

class BackgammonBlackPlayer:public BackgammonPlayer{

public:
	BackgammonBlackPlayer();
	
};

#endif
