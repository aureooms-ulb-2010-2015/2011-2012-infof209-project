#include "BackgammonMove.hpp"
#include <sstream>
#include <stdlib.h>
#include <iostream>
BackgammonMove::BackgammonMove(string data){
	this->build(data);
}

int BackgammonMove::id(){
	return this->_id;
}

string BackgammonMove::type(){
	return this->_type;
}

int BackgammonMove::exit_p(){
	return this->_exit_p;
}

int BackgammonMove::empty_p(){
	return this->_empty_p;
}
string BackgammonMove::color(){
	return this->_color;
}

int BackgammonMove::from(){
	return this->_from;
}

int BackgammonMove::to(){
	return this->_to;
}

string BackgammonMove::serialize(){
	ostringstream temp;
	temp << this->id() << this->type() << ":";
	if(this->type() == "E"){
		temp << this->exit_p();
	}
	else if(this->type() == "F"){
		temp << this->color() << ":" << this->empty_p();
	}
	
	else{
		temp << this->from() << " " << this->to();
	}
	return temp.str();
}

void BackgammonMove::build(string data){
	this->_id = atoi(data.substr(0,1).c_str());
	this->_type = data.substr(1,1);
	
	if(this->_type == "E"){
		this->_exit_p = atoi(data.substr(3).c_str());
	}
	else if(this->_type == "F"){
		this->_color = data.substr(3,1);
		this->_empty_p = atoi(data.substr(5).c_str());
	}
	
	else{
		int startPos = 3;
		int spacePos = data.find_first_of(" ",startPos);
		int gap = spacePos - startPos;
		this->_from = atoi((data.substr(startPos,gap)).c_str());
		this->_to = atoi((data.substr(spacePos+1)).c_str());
	}
}
