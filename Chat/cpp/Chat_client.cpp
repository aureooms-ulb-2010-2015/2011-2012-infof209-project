#include "../h/Chat_client.h"
#include "../../Library/Socket/SocketException.h"
#include <iostream>
#include <sstream>
#include <cstdlib>
#define APP_PORT 30000

Chat_client::Chat_client():__pseudo("default"),__channel("default"),__server("localhost"),__port(APP_PORT){}

Chat_client::Chat_client(string server, string pseudo, string channel):__pseudo(pseudo),__channel(channel),__server(server),__port(APP_PORT){}

Chat_client::~Chat_client(){
	delete this->__socket;
	delete this->__sender;
	delete this->__receiver;
}

//GETTERS
ClientSocket *Chat_client::socket(){return this->__socket;}

string Chat_client::pseudo(){return this->__pseudo;}

string Chat_client::channel(){return this->__channel;}

string Chat_client::server(){return this->__server;}

long int Chat_client::port(){return this->__port;}

Chat_client_message_sender *Chat_client::sender(){return this->__sender;}

Chat_client_message_receiver *Chat_client::receiver(){return this->__receiver;}

//SETTERS
Chat_client& Chat_client::socket(ClientSocket *socket){
	this->__socket = socket;
	return *this;
}

Chat_client& Chat_client::pseudo(string pseudo){
	this->__pseudo = pseudo;
	return *this;
}

Chat_client& Chat_client::channel(string channel){
	this->__channel = channel;
	return *this;
}

Chat_client& Chat_client::server(string server){
	this->__server = server;
	return *this;
}

Chat_client& Chat_client::port(long int port){
	this->__port = port;
	return *this;
}

Chat_client& Chat_client::sender(Chat_client_message_sender *sender){
	this->__sender = sender;
	return *this;
}

Chat_client& Chat_client::receiver(Chat_client_message_receiver *receiver){
	this->__receiver = receiver;
	return *this;
}



Chat_client& Chat_client::connect_to_channel(){
	string connected;
	ostringstream temp;
	temp << "pseudo=" << this->__pseudo << "&channel=" << this->__channel;
	string data = temp.str();
	*this->__socket << data;
	return *this;
}


void* Chat_client::run(void*){
	try{

		this->socket(new ClientSocket(this->server(),this->port()));
		this->connect_to_channel();
		this->receiver(new Chat_client_message_receiver(this));
		this->receiver()->start();
		this->sender(new Chat_client_message_sender(this));
		this->sender()->start();
		void* res;
		pthread_join(*this->receiver()->getThread(),&res);
		if ( *(int*)res == 1){
			throw SocketReadException();
		}
		pthread_join(*this->sender()->getThread(),&res);
		if ( *(int*)res == 2){
			throw SocketWriteException();
		}
	}
	catch ( SocketBindException& e ){
		cout << "Server not found" << endl;
		return new int(1);
	}
	catch ( SocketReadException& e){
		system("clear");
		ofstream file(this->receiver()->text_file_name().c_str(),ios::app);
		file << "No message will be displayed here anymore, please close this window." << endl;
		file.close();
		cout << "Server found disconnected, try to connect again." << endl;
		return new int(2);
	}
	catch ( SocketWriteException& e){
		system("clear");
		ofstream file(this->receiver()->text_file_name().c_str(),ios::app);
		file << "No message will be displayed here anymore, please close this window." << endl;
		file.close();
		cout << "Server found disconnected, try to connect again." << endl;
		return new int(3);
	}
	return 0;
}
