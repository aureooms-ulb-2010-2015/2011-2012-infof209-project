#if !defined(_CHAT_CHANNEL_STATE_H)
#define _CHAT_CHANNEL_STATE_H

#include <vector>
#include <string>
#include "Feed.h"

class Chat_channel_state {
private:
	vector<Feed*> __feeds;
public:
	Chat_channel_state();
	~Chat_channel_state();
	virtual string toString();
	virtual Chat_channel_state& push(Feed* feed);
	virtual vector<Feed*>& feeds();
	virtual Chat_channel_state& feeds(vector<Feed*> feeds);
};

#endif  //_CHAT_CHANNEL_STATE_H
