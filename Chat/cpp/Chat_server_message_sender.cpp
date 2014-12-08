#include "../h/Chat_server_message_sender.h"
#include "../h/Chat_client_manager.h"
#include "../h/communication_library.h"
#include <iostream>
#include <sstream>
#include <time.h>
using namespace std;

Chat_server_message_sender::Chat_server_message_sender(Chat_client_manager *manager,ServerSocket &socket):manager(manager),socket(&socket),pseudo("pseudotest"){}


Chat_server_message_sender::~Chat_server_message_sender(){
	delete this->socket;
}

Chat_server_message_sender& Chat_server_message_sender::send_feed(Feed *feed){
	ostringstream temp;
	temp << "?type=" << Escape_get(feed->type()) << "&data=" << Escape_get(feed->serialize());
	*this->socket << temp.str();
	return *this;

}
