#ifndef _LUDO_MOVE_H
#define _LUDO_MOVE_H

#include "../../Move.hpp"
#include <string>

class LudoMove: public Move{

private:
	int _start;
	int _finish;
	int _piece;
	int _owner;

public:
	LudoMove(int,int,int,int);
	LudoMove(std::string);

	int start();
	int finish();
	int piece();
	int owner();
	std::string serialize();
	void build(std::string);
};

#endif
