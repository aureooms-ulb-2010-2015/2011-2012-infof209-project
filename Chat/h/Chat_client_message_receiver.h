#if !defined(_CHAT_CLIENT_MESSAGE_RECEIVER_H)
#define _CHAT_CLIENT_MESSAGE_RECEIVER_H


#include "../../Library/Thread/Thread.hpp"
#include "./Chat_message.h"
#include "../../Library/Socket/ClientSocket.h"
#include <iostream>
#include <fstream>
class Chat_client;

class Chat_client_message_receiver: public Thread{

	private:
		ClientSocket *__socket;
		Chat_client *__client;
		string __text_file_name;

	public:
		Chat_client_message_receiver(Chat_client *client);

		~Chat_client_message_receiver();

		ClientSocket *socket();
		Chat_client *client();
		string text_file_name();

		Chat_client_message_receiver& socket(ClientSocket *socket);
		Chat_client_message_receiver& client(Chat_client *client);
		Chat_client_message_receiver& text_file_name(string text_file_name);

		virtual Chat_client_message_receiver& init();
		virtual void* run(void*);
		virtual void manage_message_reception();
		virtual Chat_client_message_receiver& open_frame();
};

#endif  //_CHAT_CLIENT_MESSAGE_RECEIVER_H
