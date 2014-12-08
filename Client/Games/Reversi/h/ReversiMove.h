#ifndef _REVERSI_MOVE_H
#define _REVERSI_MOVE_H


#include "../h/ReversiMove.h"
#include "../../Move.hpp"

class ReversiMove : public Move{

	private:
	
		unsigned short int _column;
		unsigned short int _row;
		unsigned short int _player;
		
	
	public:
		ReversiMove(unsigned short int,unsigned short int,unsigned short int);
		ReversiMove(std::string);
		virtual string serialize();
		virtual void build(string);
		
		unsigned short int column();
		unsigned short int row();
		unsigned short int player();
	


};

#endif //_REVERSI_MOVE_H
