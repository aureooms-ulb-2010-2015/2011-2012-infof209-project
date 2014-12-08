#if !defined(_CHAT_SERVER_MESSAGE_RECEIVER_H)
#define _CHAT_SERVER_MESSAGE_RECEIVER_H

#include "../../Library/Thread/Thread.hpp"
#include "../../Library/Socket/ServerSocket.h"

class Chat_client_manager;

class Chat_server_message_receiver: public Thread{
private:
	Chat_client_manager *manager;
	ServerSocket *socket;
public:
	Chat_server_message_receiver(Chat_client_manager *manager,ServerSocket &socket);
	~Chat_server_message_receiver();
	virtual void* run(void*);
	virtual void manage_message_reception();
};

#endif  //_CHAT_SERVER_MESSAGE_RECEIVER_H
