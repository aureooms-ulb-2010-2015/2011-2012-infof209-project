#include "Request.hpp"
#include "GenericCommunicator.hpp"
#include <iostream>
#include <sstream>

using namespace std;

/*
____________________________________________________________________________________

Contructeurs
____________________________________________________________________________________

*/

Request::Request(GenericCommunicator * gc){
    this->setCommunicator(gc);
    this->_commands="";
}

/*
____________________________________________________________________________________

Méthodes manipulation de l'objet
____________________________________________________________________________________

*/

string Request::getSequence(){
    string sequence = this->getType()+":"+this->getName()+":";
    for(unsigned int i = 0; i<this->getAttributes().size(); ++i){
        sequence+=this->getAttributes()[i]+":";
    }
    if(this->getAttributes().empty()){
        sequence+=".:";
    }
    sequence+=";";
    return sequence;
}

void Request::parseString(string str){
    size_t first, last;
	string attribute;
	string message;
	int i=0;
	first=0;
	last=str.find_first_of(':');
	while(last!=string::npos){
		if(str[last-1]=='\\'){
			str.erase(last-1,1);
			last=str.find_first_of(':',last);
		}
		else{
			if(i==0){
				this->_type=str.substr(first,last-first);
			}
			else if(i==1){
				this->_name=str.substr(first,last-first);
			}
			else{
				this->_attributes.push_back(str.substr(first,last-first));
			}
			first=last+1;
			last=str.find_first_of(':',last+1);
			++i;
        }
	}
}

unsigned int Request::loadNextCommand(){
    size_t last,first=0;
	string command;
	this->clear();
	last=this->getCommands().find_first_of(';');
	while(true){
	    if(last==string::npos || this->getCommands().size()<5){
	        return 0;
	    }
	    else if(this->getCommands()[last-1]=='\\'){
			this->getCommands().erase(last-1,1);
			last=this->getCommands().find_first_of(';',last);
		}
	    else{
	        command=this->getCommands().substr(first,last-first);
	        this->parseString(command);
	        this->_commands = this->getCommands().substr(last-first+1,this->_commands.size());
	        return command.length();
	    }
    }
}

string Request::addSlashes(string str){
	string message;
	message=this->slashChar(str,':');
	message=this->slashChar(message,';');
	return message;
}

string Request::slashChar(string str, char c){
    size_t first, last;
	string attribute;
	string message="";
	first=0;
	last=str.find_first_of(c);
	while(last!=string::npos){
	    message+=str.substr(first,last-first)+"\\"+c;
	    first=last+1;
		last=str.find_first_of(c,last+1);
	}
	message+=str.substr(first,str.length());
	return message;
}

void Request::makeRequest(string type, string name){
    if(! this->isEmpty()){
        this->_commands+=this->getSequence();
        this->clear();
    }
    this->setType(type);
    this->setName(name);
}

void Request::makeRequest(const char * type, const char * n){
    string name=n;
    this->makeRequest(type,name);
}

void Request::makeRequest(const char * t, string name){
    string type =t;
    this->makeRequest(type,name);
}

void Request::clear(){
    this->_type= "";
    this->_name= "";
    while(! this->_attributes.empty()){
        this->_attributes.pop_back();
    }
}

bool Request::isEmpty(){
    return this->getType().empty() || this->getName().empty();
}

/*
____________________________________________________________________________________

Méthodes synchrones
____________________________________________________________________________________

*/

void Request::set(string name, string attr){
    this->makeRequest("SET",name);
    this->addAttribute(attr);
    this->getCommunicator()->sendRequest(this);
}

void Request::set(const char * n, string attr){
    string name = n;
    this->set(name, attr);
}

void Request::set(const char * name, const char * a){
    string attr=a;
    this->set(name, attr);
}

void Request::set(const char * name, int i){
    ostringstream temp;
    temp<<i;
    this->set(name, temp.str());
}

void Request::set(string name, int i){
    ostringstream temp;
    temp<<i;
    this->set(name, temp.str());
}

void Request::getRequest(string name, string attr){
    this->makeRequest("GET",name);
    this->addAttribute(attr);
    this->getCommunicator()->sendRequest(this);
}

string Request::get(string name, string attr){
    string message;
    this->getRequest(name, attr);
    this->getCommunicator()->recvMessage(message);
    return message;
}

string Request::get(const char * name, string attr){
   string n=name;
   return this->get(n,attr);
}

string Request::get(const char * name, const char * a){
   string n=name;
   string attr = a;
   return this->get(n,attr);
}

int Request::getInt(string name, string attr){
    this->getRequest(name, attr);
    return this->getCommunicator()->recvInt();
}

int  Request::getInt(const char * name, string attr){
   string n=name;
   return this->getInt(n,attr);
}

int Request::getInt(const char * name, const char * a){
   string n=name;
   string attr = a;
   return this->getInt(n,attr);
}

bool Request::getBool(string name, string attr){
    this->getRequest(name, attr);
    return this->getCommunicator()->recvBool();
}

bool  Request::getBool(const char * name, string attr){
   string n=name;
   return this->getBool(n,attr);
}

bool Request::getBool(const char * name, const char * a){
   string n=name;
   string attr = a;
   return this->getBool(n,attr);
}

/*
____________________________________________________________________________________

Méthodes asynchrones
____________________________________________________________________________________

*/

void Request::flush(){
    this->getCommunicator()->sendRequest(this);
    this->clear();
    this->_commands="";
}


/*
____________________________________________________________________________________

Setters et Adders
____________________________________________________________________________________

*/

void Request::setType(string type){
    this->_type = this->addSlashes(type);
}

void Request::setType(const char * type){
    string t = type;
    this->_type = this->addSlashes(t);
}

void Request::setName(string name){
    this->_name=this->addSlashes(name);
}

void Request::setName(const char * name){
    string n = name;
    this->_name=this->addSlashes(n);
}

void Request::addAttribute(string attr){
    this->_attributes.push_back(this->addSlashes(attr));
}

void Request::addAttribute(const char * attribute){
    string attr = attribute;
    this->_attributes.push_back(this->addSlashes(attr));
}

void Request::addAttribute(int i){    
    ostringstream temp;
    temp<<i;
    this->addAttribute(temp.str());
}

