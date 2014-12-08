#include "../h/VerticalDirection.h"

VerticalDirection::VerticalDirection(int shift) : Direction(shift){

}

bool VerticalDirection::up() {
	return this->back();
}

bool VerticalDirection::down() {
	return this->forward();

}

