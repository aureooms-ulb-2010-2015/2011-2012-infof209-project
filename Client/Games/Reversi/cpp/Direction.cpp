#include "../h/Direction.h"


const short int Direction::__BACKWARD = -1;
const short int Direction::__FORWARD = 1;
const short int Direction::__NO_MOVEMENT = 0;
const short int Direction::__REFERER = 0;


Direction::Direction(int shift):__direction(shift){
}

bool Direction::back() {
	return this->__direction < Direction::__REFERER;
}

bool Direction::forward() {
	return this->__direction > Direction::__REFERER;

}

bool Direction::no_movement() {
	return this->__direction == Direction::__REFERER;

}

int Direction::toInt(){
	if (this->back()){
		return Direction::__BACKWARD;
	}
	else if (this->forward()){
		return Direction::__FORWARD;
	}
	else{
		return Direction::__NO_MOVEMENT;
	}
}

