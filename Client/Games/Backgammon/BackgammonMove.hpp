#ifndef _BACKGAMMON_MOVE_H
#define _BACKGAMMON_MOVE_H

#include "../Move.hpp"

class BackgammonMove: public Move{

private:
	int _id;
	string _type;
	int _exit_p;
	int _empty_p;
	string _color;
	int _from;
	int _to;

public:
	BackgammonMove(std::string);

	int id();
	string type();
	int exit_p();
	int empty_p();
	string color();
	int from();
	int to();

	string serialize();
	void build(string);
};

#endif
