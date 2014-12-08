
#include "../h/ReversiMove.h"
#include <string>
#include <sstream>

ReversiMove::ReversiMove(unsigned short int column ,unsigned short int row ,unsigned short int id){
	this->_column=column;
	this->_row=row;
	this->_player=id;
}


ReversiMove::ReversiMove(string data){
	this->build(data);
}

unsigned short int ReversiMove::player(){

	return this->_player;
}
unsigned short int ReversiMove::row(){

	return this->_row;
}
unsigned short int ReversiMove::column(){

	return this->_column;
}
string ReversiMove::serialize(){
    ostringstream temp;
    temp << this->column() << this->row() << this->player();
    return temp.str();
}
void ReversiMove::build(string data){
	
	istringstream c_caster(data.substr(0,1));
	istringstream r_caster(data.substr(1,1));
	istringstream p_caster(data.substr(2,1));
	c_caster >> this->_column;
	r_caster >> this->_row;
	p_caster >> this->_player;
}
