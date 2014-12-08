#if !defined(_REVERSIBLACKPLAYER_H)
#define _REVERSIBLACKPLAYER_H

#include "ReversiPlayer.h"

using namespace std;

class ReversiBlackPlayer : public ReversiPlayer {
public:
	static string _NAME;

	ReversiBlackPlayer();
	string toString();
};

#endif  //_REVERSIBLACKPLAYER_H
