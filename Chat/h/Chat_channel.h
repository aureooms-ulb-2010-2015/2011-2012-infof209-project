#if !defined(_CHAT_CHANNEL_H)
#define _CHAT_CHANNEL_H

#include <vector>
#include <string>
#include "./Chat_channel_state.h"
#include "./Chat_client_manager.h"
#include "./Feed.h"
//class Feed;

class Chat_channel {
private:
	vector<Chat_client_manager*> clients;
	string id;
	Chat_channel_state *state;
public:
	Chat_channel();
	Chat_channel(string id);
	~Chat_channel();
	virtual Chat_channel& add_client(Chat_client_manager *client);
	virtual Chat_channel& remove_client(Chat_client_manager &client);
	virtual Chat_channel_state* get_state();
	virtual	bool is(string id);
	virtual	string get_id();
	virtual void push(Feed *feed);
};

#endif  //_CHAT_CHANNEL_H
