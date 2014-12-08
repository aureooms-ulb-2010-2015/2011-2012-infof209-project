#if !defined(_TRINARYSTATE_H)
#define _TRINARYSTATE_H


using namespace std;

class TrinaryState {
private:
	unsigned short int __actual;
	
public:
	static const unsigned short int __FIRST;
	static const unsigned short int __SECOND;
	static const unsigned short int __THIRD;
	
	TrinaryState();
	virtual bool first();
	virtual bool second();
	virtual bool third();
	virtual TrinaryState& setFirst();
	virtual TrinaryState& setSecond();
	virtual TrinaryState& setThird();
};

#endif  //_TRINARYSTATE_H
