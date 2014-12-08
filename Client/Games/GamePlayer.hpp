#ifndef _GAMEPLAYER_Hdd
#define _GAMEPLAYER_Hdd
#include <string>
using namespace std;

class GamePlayer{

private:
	string _name;

public:
	GamePlayer();
	GamePlayer(string);
	virtual string toString();
};

#endif
