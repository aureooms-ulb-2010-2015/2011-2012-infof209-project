#if !defined(_REVERSIPLAYER_H)
#define _REVERSIPLAYER_H

#include <string>
#include "../../GamePlayer.hpp"

using namespace std;

class ReversiPlayer : public GamePlayer{
private:
	bool _color;
	
public:
	static const bool _BLACK;
	static const bool _WHITE;
	
	ReversiPlayer(bool color);
	virtual bool black();
	virtual bool white();
};

#endif  //_REVERSIPLAYER_H
