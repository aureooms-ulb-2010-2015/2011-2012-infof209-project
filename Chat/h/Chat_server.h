#if !defined(_CHAT_SERVER_H)
#define _CHAT_SERVER_H

#include "./Chat_channel.h"
#include "./Chat_client_manager.h"
#include <vector>
#include <map>
#include "../../Library/Thread/Thread.hpp"
#include "../../Library/Socket/ServerSocket.h"


class Chat_server: public Thread{
	private:
		vector<Chat_channel*> channels;
		ServerSocket socket;
		int port;
	public:
		~Chat_server();
		virtual void* run(void*);
		virtual Chat_server& remove_channel(string id);
		virtual Chat_server& receive_client_connection_to_channel();
		virtual Chat_server& create_channel(string id);
		virtual Chat_server& add_client_to_channel(Chat_client_manager *client, string id);
		virtual Chat_server& remove_client_from_channel(Chat_client_manager &client, string id);
		virtual bool channel_exists(string id);
		virtual Chat_channel* get_channel(string id);
		virtual map<string,string> decode(string encoded);
};

#endif  //_CHAT_SERVER_H
