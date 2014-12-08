#include "../Chat_client_header/Chat_client.h"
#include "../Chat_client_header/Chat_client_message_receiver.h"
#include "../../../Library/Socket/SocketException.h"
#include "../Chat_client_header/Chat_message.h"
#include "../Chat_client_header/Chat_notification.h"
#include "../Chat_client_header/communication_library.h"
#include <sstream>
#include <cstdlib>
#include <stdio.h>
#include <time.h>

Chat_client_message_receiver::Chat_client_message_receiver(Chat_client *client):__socket(new ClientSocket (client->server(),client->port())),__client(client){
	time_t timestamp;
	timestamp = time (NULL);
	ostringstream temp;
	temp << "./client_files/" << this->client()->pseudo() << "_" << timestamp;
	string filename = temp.str();
	filename = valid_filename(filename);
	this->text_file_name(filename);
        /*ofstream file(this->text_file_name().c_str());
	file << "Messages will be shown here." << endl;
        file.close();*/
}

Chat_client_message_receiver::~Chat_client_message_receiver(){
	delete this->__socket;
}

Chat_client_message_receiver& Chat_client_message_receiver::init(){
        //this->open_frame();
	return *this;
}


void Chat_client_message_receiver::manage_message_reception(){
	string encoded;
	try{
		*this->socket() >> encoded;
		vector<string> feeds =  Split_get(encoded,"?");
		vector<string>::iterator it;
		for (it = feeds.begin();it != feeds.end();it++){
			if(Deserialize(*it).find("type")->second.compare("message") == 0){
                                //ofstream file(this->text_file_name().c_str(),ios::app);
                                //file << Chat_message(Deserialize(*it).find("data")->second).toString() << endl;
                                //file.close();
                            emit received(QString(Chat_message(Deserialize(*it).find("data")->second).toString().c_str()));
			}
			else if(Deserialize(*it).find("type")->second.compare("notification") == 0){
                                //ofstream file(this->text_file_name().c_str(),ios::app);
                                //file << Chat_notification(Deserialize(*it).find("data")->second).toString() << endl;
                                //file.close();
                            emit received(QString(Chat_notification(Deserialize(*it).find("data")->second).toString().c_str()));
			}
		}
	}
	catch( SocketReadException& e ){
		cout << "Interrupted while waiting for message." << endl;
		throw e;
	}
}


Chat_client_message_receiver& Chat_client_message_receiver::open_frame(){
	ostringstream temp;
	temp << "gnome-terminal -e 'tail -c +0 -f " << this->text_file_name() << "'";
	string cmd = temp.str();
	system(cmd.c_str());
	return *this;
}


ClientSocket* Chat_client_message_receiver::socket(){
	return this->__socket;
}
Chat_client* Chat_client_message_receiver::client(){
	return this->__client;
}
string Chat_client_message_receiver::text_file_name(){
	return this->__text_file_name;
}

Chat_client_message_receiver& Chat_client_message_receiver::socket(ClientSocket *socket){
	this->__socket = socket;
	return *this;
}
Chat_client_message_receiver& Chat_client_message_receiver::client(Chat_client *client){
	this->__client = client;
	return *this;
}
Chat_client_message_receiver& Chat_client_message_receiver::text_file_name(string text_file_name){
	this->__text_file_name = text_file_name;
	return *this;
}

void* Chat_client_message_receiver::run(void*){
	this->init();
	try{
		while(true){
			this->manage_message_reception();
		}
	}
	catch ( SocketReadException& e ){
		return new int(1);
	}
	return 0;
}
