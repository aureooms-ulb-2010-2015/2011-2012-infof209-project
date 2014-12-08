#include "../h/HorizontalDirection.h"

HorizontalDirection::HorizontalDirection(int shift): Direction(shift) {

}

bool HorizontalDirection::left() {
	return this->back();

}

bool HorizontalDirection::right() {
	return this->forward();

}

