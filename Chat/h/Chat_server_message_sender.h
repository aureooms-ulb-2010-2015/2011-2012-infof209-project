#if !defined(_CHAT_SERVER_MESSAGE_SENDER_H)
#define _CHAT_SERVER_MESSAGE_SENDER_H

#include "../../Library/Socket/ServerSocket.h"
#include "./Feed.h"
#include "./Chat_notification.h"
#include <string>

class Chat_client_manager;

class Chat_server_message_sender{
private:
	Chat_client_manager *manager;
	ServerSocket *socket;
	string pseudo;
public:
	Chat_server_message_sender(Chat_client_manager *manager,ServerSocket &socket);
	~Chat_server_message_sender();
	virtual Chat_server_message_sender& send_feed(Feed *feed);
};

#endif  //_CHAT_SERVER_MESSAGE_SENDER_H
