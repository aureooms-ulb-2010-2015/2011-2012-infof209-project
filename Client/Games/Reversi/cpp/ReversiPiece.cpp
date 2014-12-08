#include "../h/ReversiPiece.h"

string ReversiPiece::__BLACK = "N";
string ReversiPiece::__WHITE = "B";
string ReversiPiece::__UNSET = "U";

ReversiPiece::ReversiPiece() : Piece("R"),__state(new TrinaryState){
	this->init();
}
ReversiPiece::~ReversiPiece() {
	delete this->__state;
}

bool ReversiPiece::black() {
	return this->__state->first();

}

bool ReversiPiece::white() {
	return this->__state->second();
}

bool ReversiPiece::not_set() {
	return this->__state->third();
}

ReversiPiece& ReversiPiece::reverse() {
	if (this->white()){
		this->setBlack();
	}
	else if (this->black()){
		this->setWhite();
	}
	return *this;
}

ReversiPiece& ReversiPiece::setBlack() {
	this->__state->setFirst();
	return *this;

}

ReversiPiece& ReversiPiece::setWhite() {
	this->__state->setSecond();
	return *this;

}

ReversiPiece& ReversiPiece::unset() {
	this->__state->setThird();
	return *this;

}

ReversiPiece& ReversiPiece::init() {
	this->unset();
	return *this;
}

string ReversiPiece::toString(){
	if (this->black()){
		return ReversiPiece::__BLACK;
	}
	else if (this->white()){
		return ReversiPiece::__WHITE;
	}
	else {
		return ReversiPiece::__UNSET;
	}
}
