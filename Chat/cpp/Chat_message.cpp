#include "../h/Chat_message.h"
#include <stdlib.h>
#include <sstream>


Chat_message::Chat_message(long int timestamp,string author,string content){
	this->type("message");
	this->timestamp(timestamp);
	this->author(author);
	this->content(content);
}

Chat_message::Chat_message(string encoded){
	this->type("message");
	map<string,string> pairs = this->deserialize(encoded);
	this->timestamp(atol((pairs.find("timestamp")->second).c_str()));
	this->author(pairs.find("author")->second);
	this->content(pairs.find("content")->second);
}

string Chat_message::toString() {
	ostringstream temp;
	temp << this->time();
	temp << " " << this->author() << " : " << this->content();
	string result = temp.str();
	return result;
}
