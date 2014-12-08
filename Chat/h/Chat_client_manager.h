#if !defined(_CHAT_CLIENT_MANAGER_H)
#define _CHAT_CLIENT_MANAGER_H

#include "./Chat_server_message_receiver.h"
#include "./Chat_server_message_sender.h"
#include "../../Library/Socket/ServerSocket.h"
#include <string>

class Chat_channel;

class Chat_client_manager {
private:
	string pseudo;
	Chat_channel *channel;
	ServerSocket *socket;
	Chat_server_message_receiver receiver;
	Chat_server_message_sender sender;
public:
	Chat_client_manager(string pseudo,Chat_channel *channel,ServerSocket &socket,ServerSocket &r_sock,ServerSocket &s_sock);
	~Chat_client_manager();
	virtual Chat_channel* get_channel();
	virtual Chat_server_message_receiver& get_receiver();
	virtual Chat_server_message_sender& get_sender();
	virtual string get_pseudo();
};

#endif  //_CHAT_CLIENT_MANAGER_H
