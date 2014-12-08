#ifndef CHECKERSMOVE_HPP_INCLUDED
#define CHECKERSMOVE_HPP_INCLUDED

#include "../Move.hpp"

#include <string>
#include <sstream>

using namespace std;

class CheckersMove : public Move{
protected:
	int _rowi;
	int _columni;
	int _rowf;
	int _columnf;
public:
	CheckersMove(string);
	CheckersMove(int,int,int,int);
	string serialize();
	void build(string);
	int row_s();
	int row_e();
	int column_e();
	int column_s();





};




#endif
