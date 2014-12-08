#include "../h/TrinaryState.h"

const unsigned short int TrinaryState::__FIRST = 0;
const unsigned short int TrinaryState::__SECOND = 1;
const unsigned short int TrinaryState::__THIRD = 2;

TrinaryState::TrinaryState(){
}

bool TrinaryState::first() {
	return this->__actual == TrinaryState::__FIRST;
}

bool TrinaryState::second() {
	return this->__actual == TrinaryState::__SECOND;

}

bool TrinaryState::third() {
	return this->__actual == TrinaryState::__THIRD;

}

TrinaryState& TrinaryState::setFirst() {
	this->__actual = TrinaryState::__FIRST;
	return *this;

}

TrinaryState& TrinaryState::setSecond() {
	this->__actual = TrinaryState::__SECOND;
	return *this;

}

TrinaryState& TrinaryState::setThird() {
	this->__actual = TrinaryState::__THIRD;
	return *this;

}

