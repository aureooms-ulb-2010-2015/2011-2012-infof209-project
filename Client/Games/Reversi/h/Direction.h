#if !defined(_DIRECTION_H)
#define _DIRECTION_H

using namespace std;

class Direction {
private:
	short int __direction;
	
public:
	static const short int __BACKWARD;
	static const short int __FORWARD;
	static const short int __NO_MOVEMENT;
	static const short int __REFERER;

	Direction(int shift);
	virtual bool back();
	virtual bool forward();
	virtual bool no_movement();
	virtual int toInt();
};

#endif  //_DIRECTION_H
