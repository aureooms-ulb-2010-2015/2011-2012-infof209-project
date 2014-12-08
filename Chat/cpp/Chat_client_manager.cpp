#include "../h/Chat_client_manager.h"
#include "../h/Chat_channel.h"

Chat_client_manager::Chat_client_manager(string pseudo, Chat_channel *channel,ServerSocket &socket,ServerSocket &r_sock,ServerSocket &s_sock):pseudo(pseudo),channel(channel),socket(&socket),receiver(this,r_sock),sender(this,s_sock){
	this->receiver.start();
}

Chat_client_manager::~Chat_client_manager(){
	delete this->socket;
}


Chat_channel* Chat_client_manager::get_channel(){
	return this->channel;
}


Chat_server_message_receiver& Chat_client_manager::get_receiver(){
	return this->receiver;
}


Chat_server_message_sender& Chat_client_manager::get_sender(){
	return this->sender;
}

string Chat_client_manager::get_pseudo(){
	return this->pseudo;
}
