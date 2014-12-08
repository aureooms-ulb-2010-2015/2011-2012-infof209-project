#include "../h/Chat_server_message_receiver.h"
#include "../../Library/Socket/SocketException.h"
#include "../h/Chat_client_manager.h"
#include "../h/Chat_channel.h"
#include "../h/Chat_message.h"


Chat_server_message_receiver::Chat_server_message_receiver(Chat_client_manager *manager,ServerSocket &socket):manager(manager),socket(&socket){
}

Chat_server_message_receiver::~Chat_server_message_receiver(){
	delete this->socket;
}

void Chat_server_message_receiver::manage_message_reception(){
	string encoded;
	*this->socket >> encoded;
	cout << "Propaging '" << encoded << "' on '" << this->manager->get_channel()->get_id() << "'." << endl;
	this->manager->get_channel()->push(new Chat_message(encoded));
}

void* Chat_server_message_receiver::run(void*){
	while(true){
		try{
			this->manage_message_reception();
		}
		catch ( SocketException& e ){
			cout << "'" << this->manager->get_pseudo() << "' found disconnected." << endl;
			cout << "Removing '"<< this->manager->get_pseudo() <<"' from '" << this->manager->get_channel()->get_id() << "'." << endl;
			this->manager->get_channel()->remove_client(*this->manager);
			return 0;
		}
	}
	return 0;
}
