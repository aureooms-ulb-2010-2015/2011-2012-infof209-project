#ifndef _MOVE_Hdk
#define _MOVE_Hdk

#include <string>
using namespace std;

class Move{

public:
	virtual string serialize()=0;
	virtual void build(string)=0;

};

#endif
