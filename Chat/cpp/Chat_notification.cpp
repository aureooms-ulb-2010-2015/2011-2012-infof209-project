#include "../h/Chat_notification.h"
#include <stdlib.h>
#include <sstream>
#include <cstdlib>


Chat_notification::Chat_notification(string author,string content){
	this->type("notification");
	this->timestamp(::time(NULL));
	this->author(author);
	this->content(content);
}

Chat_notification::Chat_notification(string encoded){
	this->type("notification");
	map<string,string> pairs = this->deserialize(encoded);
	this->timestamp(atol((pairs.find("timestamp")->second).c_str()));
	this->author(pairs.find("author")->second);
	this->content(pairs.find("content")->second);
}

string Chat_notification::toString() {
	ostringstream temp;
	temp << this->time();
	temp << " " << this->content();
	string result = temp.str();
	return result;
}
