#if !defined(_REVERSIWHITEPLAYER_H)
#define _REVERSIWHITEPLAYER_H

#include "ReversiPlayer.h"
using namespace std;


class ReversiWhitePlayer : public ReversiPlayer {
public:
	static string _NAME;

	ReversiWhitePlayer();
	string toString();
};

#endif  //_REVERSIWHITEPLAYER_H
