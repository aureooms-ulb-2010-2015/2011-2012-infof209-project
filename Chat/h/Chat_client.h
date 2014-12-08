#if !defined(_CHAT_CLIENT_H)
#define _CHAT_CLIENT_H

#include <string>
#include "../../Library/Thread/Thread.hpp"
#include "./Chat_client_message_receiver.h"
#include "./Chat_client_message_sender.h"
#include "../../Library/Socket/ClientSocket.h"

class Chat_client: public Thread {
private:
	ClientSocket *__socket;
	string __pseudo;
	string __channel;
	string __server;
	long int __port;
	Chat_client_message_sender *__sender;
	Chat_client_message_receiver *__receiver;
public:
	//CONSTRUCTORS
	Chat_client();
	Chat_client(string server, string pseudo, string channel);

	//DESTRUCTOR
	~Chat_client();

	//GETTERS
	ClientSocket *socket();
	string pseudo();
	string channel();
	string server();
	long int port();
	Chat_client_message_sender *sender();
	Chat_client_message_receiver *receiver();

	//SETTERS
	Chat_client& socket(ClientSocket *socket);
	Chat_client& pseudo(string pseudo);
	Chat_client& channel(string channel);
	Chat_client& server(string server);
	Chat_client& port(long int port);
	Chat_client& sender(Chat_client_message_sender *sender);
	Chat_client& receiver(Chat_client_message_receiver *receiver);

	//MISCELLANEOUS
	virtual Chat_client& connect_to_channel();

	//THREAD
	virtual void* run(void*);
};

#endif  //_CHAT_CLIENT_H
