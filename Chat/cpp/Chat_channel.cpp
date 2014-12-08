#include "../h/Chat_channel.h"
#include "../h/Chat_channel_state.h"
#include "../h/communication_library.h"
//#include "../h/Chat_message.h"

Chat_channel::Chat_channel():id("test"),state(new Chat_channel_state()){
}

Chat_channel::Chat_channel(string id):id(id),state(new Chat_channel_state()){
}

Chat_channel::~Chat_channel(){
	vector<Chat_client_manager*>::iterator iterator;
    
    	for(iterator = this->clients.begin(); iterator!=this->clients.end(); ++iterator){
		delete *iterator;
	}

	delete this->state;
}


Chat_channel& Chat_channel::add_client(Chat_client_manager *client){
	this->clients.push_back(client);
	
	vector<Feed*>::iterator feed;
	for(feed = this->state->feeds().begin(); feed!=this->state->feeds().end(); ++feed){
		client->get_sender().send_feed((*feed));
	}	

	this->push(new Chat_notification("server","'"+client->get_pseudo() +"' a rejoint le canal " + this->id + "."));
	return *this;
}

Chat_channel& Chat_channel::remove_client(Chat_client_manager &client){

	vector<Chat_client_manager*>::iterator iterator;
    
    	for(iterator = this->clients.begin(); iterator!=this->clients.end(); ++iterator){
		if (*iterator == &client){
			this->push(new Chat_notification("server","'"+(*iterator)->get_pseudo() +"' a quitté le chat."));
			this->clients.erase(iterator);
			break;
		}
	}
	return *this;
}


Chat_channel_state* Chat_channel::get_state(){

	return this->state;
	
}

bool Chat_channel::is(string id){
	return this->id == id;
}

string Chat_channel::get_id(){
	return this->id;
}

void Chat_channel::push(Feed* feed){
	this->state->push(feed);
	vector<Chat_client_manager*>::iterator iterator;
    
	for(iterator = this->clients.begin(); iterator!=this->clients.end(); ++iterator){
		(*iterator)->get_sender().send_feed(feed);

	}
	
}
