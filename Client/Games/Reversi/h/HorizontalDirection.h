#if !defined(_HORIZONTALDIRECTION_H)
#define _HORIZONTALDIRECTION_H

#include "Direction.h"

using namespace std;

class HorizontalDirection : public Direction {
public:
	HorizontalDirection(int shift);
	virtual bool left();
	virtual bool right();
};

#endif  //_HORIZONTALDIRECTION_H
