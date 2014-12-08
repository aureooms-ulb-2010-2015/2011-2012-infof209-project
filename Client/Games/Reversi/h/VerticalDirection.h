#if !defined(_VERTICALDIRECTION_H)
#define _VERTICALDIRECTION_H

#include "Direction.h"

using namespace std;

class VerticalDirection : public Direction {
public:
	VerticalDirection(int shift);
	virtual bool up();
	virtual bool down();
};

#endif  //_VERTICALDIRECTION_H
