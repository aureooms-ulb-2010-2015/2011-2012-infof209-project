#include "LudoMove.hpp"
#include <sstream>
#include <string>
#include <stdlib.h>
#include <iostream>

using namespace std;

LudoMove::LudoMove(int start, int finish, int piece, int owner): _start(start), _finish(finish), _piece(piece), _owner(owner) {}

LudoMove::LudoMove(string data){
	this->build(data);
}

int LudoMove::start(){
	return this->_start;
}

int LudoMove::piece(){
	return this->_piece;
}

int LudoMove::finish(){
	return this->_finish;
}

int LudoMove::owner(){
	return this->_owner;
}

string LudoMove::serialize(){
	ostringstream temp;
	temp << this->start() << "%" << this->finish() << "%" << this->piece() << "%" << this->owner() << "%";
	return temp.str();
}

void LudoMove::build(string data){
	unsigned int i=0;
	int counter=0;
	ostringstream oss;
	
	while (i<data.size()){
		
		if (data[i]!='%'){
			oss<<data[i];
		}
		else{
			if(counter==0){
				this->_start=(atoi((char *) oss.str().c_str()));
			}
			else if (counter==1){
				this->_finish=((atoi((char *) oss.str().c_str())));
			}
			else if (counter==2){
				this->_piece=atoi((char *) oss.str().c_str());
			}
			else if (counter==3){
				this->_owner=atoi((char *) oss.str().c_str());
			}
			oss.str("");
			counter++;
		}
		i++;
	}
	
}




















