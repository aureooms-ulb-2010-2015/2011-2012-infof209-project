#include "../h/Feed.h"
#include "../h/communication_library.h"
#include <sstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

//GETTERS
string Feed::type(){return this->__type;}
string Feed::author(){return this->__author;}
string Feed::content(){return this->__content;}
long int Feed::timestamp(){return this->__timestamp;}

//SETTERS
Feed& Feed::type(string type){
	this->__type = type;
	return *this;
}

Feed& Feed::author(string author){
	this->__author = author;
	return *this;
}

Feed& Feed::content(string content){
	this->__content = content;
	return *this;
}

Feed& Feed::timestamp(long int timestamp){
	this->__timestamp = timestamp;
	return *this;
}

//ENCODING


string Feed::serialize(){
	ostringstream temp_timestamp;
	temp_timestamp << this->timestamp();
	ostringstream temp;
	temp << "timestamp=" << Escape_get(temp_timestamp.str()) << "&author=" << Escape_get(this->author()) << "&content=" << Escape_get(this->content());
	string result = temp.str();
	return result;
}

map<string,string> Feed::deserialize(string encoded){
	map<string,string> result;
	vector<string> pairs =  Split_get(encoded,"&");
	vector<string>::iterator iterator;
	for (iterator=pairs.begin(); iterator!=pairs.end(); ++iterator){
		string couple = *iterator;
		string attribute =  Unescape_get(Split_get(couple,"=")[0]);
		string value =  Unescape_get(Split_get(couple,"=")[1]);
		result.insert(pair<string,string>(attribute,value));
	}
	return result;
}

//TIMESTAMP DECODING

string Feed::time(){
	time_t message_time(this->timestamp());
	struct tm *particles = gmtime(&message_time);
	ostringstream hour_temp;
	hour_temp << (particles->tm_hour+2)%24;
	string hours(hour_temp.str());
	if (hours.size() == 1){
		hours.insert(0,"0");
	}
	ostringstream min_temp;
	min_temp << particles->tm_min;
	string minutes(min_temp.str());
	if (minutes.size() == 1){
		minutes.insert(0,"0");
	}
	ostringstream sec_temp;
	sec_temp << particles->tm_sec;
	string seconds(sec_temp.str());
	if (seconds.size() == 1){
		seconds.insert(0,"0");
	}
	ostringstream temp;
	temp << "[" << hours << ":" << minutes << ":" << seconds << "]";
	return temp.str();
}
