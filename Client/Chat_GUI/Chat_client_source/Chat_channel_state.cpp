#include "../Chat_client_header/Chat_channel_state.h"
#include <iostream>

Chat_channel_state::Chat_channel_state(){}

Chat_channel_state::~Chat_channel_state(){
	vector<Feed*>::iterator feed;
	
	for(feed = this->__feeds.begin(); feed!=this->__feeds.end(); ++feed){
		delete *feed;
	}
}

string Chat_channel_state::toString() {
	string result = "";
	vector<Feed*>::iterator feed;
	
	for(feed = this->__feeds.begin(); feed!=this->__feeds.end(); ++feed){
		result.append((*feed)->toString());
	}
	
	return result;
}

Chat_channel_state& Chat_channel_state::push(Feed* feed){
	this->__feeds.push_back(feed);
	return *this;
}

vector<Feed*>& Chat_channel_state::feeds(){
	return this->__feeds;
}


Chat_channel_state& Chat_channel_state::feeds(vector<Feed*> feeds){
	this->__feeds = feeds;
	return *this;
}
