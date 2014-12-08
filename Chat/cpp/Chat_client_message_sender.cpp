#include "../h/Chat_client.h"
#include "../h/Chat_client_message_sender.h"
#include "../../Library/Socket/SocketException.h"
#include <sstream>
#include <iostream>
#include <cstdlib>

Chat_client_message_sender::Chat_client_message_sender(Chat_client *client):socket(new ClientSocket (client->server(),client->port())),client(client){}

Chat_client_message_sender::~Chat_client_message_sender(){
	delete this->socket;
}

Chat_client_message_sender& Chat_client_message_sender::send_message(Chat_message &message){
	string encoded = message.serialize();
	try{
		*this->socket << encoded;
	}
	catch( SocketWriteException& e ){
		cout << "Could not send message." << endl;
		throw e;
	}
	return *this;
}

void* Chat_client_message_sender::run(void*){
	system("clear");
	try{
		while(true){
			string text = "";
			cout << "Tapez votre message ci-dessous :" << endl;
			getline(cin,text);
			system("clear");
			if(text != ""){		
				time_t timestamp;
				timestamp = time (NULL);
				Chat_message message(timestamp,this->client->pseudo(),text);
				this->send_message(message);
			}
		}
	}
	catch( SocketWriteException& e ){
		return new int(2);
	}
	return 0;
}
