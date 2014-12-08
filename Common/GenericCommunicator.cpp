#include <iostream>
#include <string>
#include <sstream>
#include "Request.hpp"
#include "GenericCommunicator.hpp"
#include "GenericServer.hpp"
#include "../Library/all.hpp"

#define BUFFER_LENGTH 64
#define LENGTH_NAME 64

using namespace std;

/*
____________________________________________________________________________________

Constructeurs
____________________________________________________________________________________

*/

int GenericCommunicator::getSocket(){
	return this->_sockFd;
}

void GenericCommunicator::setSocket(int socket){
	this->_sockFd=socket;
}

/*
____________________________________________________________________________________

Senders
____________________________________________________________________________________

*/

void GenericCommunicator::sendMessage(string & str){
	char buffer[BUFFER_LENGTH];
	unsigned int j,i=0;
	for(i=0;i<str.size();++i){
		j=i%(BUFFER_LENGTH);
		buffer[j]=str[i];
		if((j==BUFFER_LENGTH-1) || i==str.size()-1){
			buffer[j+1]='\0';
			if(send(this->getSocket(),buffer,strlen(buffer),0)==-1){
				throw new ConnectionException("probleme while sending data.");
			}
		}
	}
}



void GenericCommunicator::sendInt(int i){
    ostringstream strStream;
    strStream<<"%INT%="<<i;
    string message=strStream.str();
    this->sendMessage(message);
}

void GenericCommunicator::sendBool(bool b){
    string message=(b)?"true":"false";
    this->sendMessage(message);
}


void GenericCommunicator::sendRequest(Request * request){
    string message =request->getCommands()+request->getSequence();
    this->sendMessage(message);
    request->clear();
}

/*
____________________________________________________________________________________

Recevers
____________________________________________________________________________________

*/

void GenericCommunicator::recvMessage(string & str){

	if(!str.empty()){
		str.erase(str.begin(),str.end());
	}
	int size=0;
	char buffer[BUFFER_LENGTH+1];

	while((size=recv(this->getSocket(),buffer,BUFFER_LENGTH,0))>0){
		buffer[size]='\0';
		str.append(buffer);
		if(size<BUFFER_LENGTH){
			break;
		}
	}
	if(size<=0){
		throw new ConnectionException("Problem while recieving data.");
	}
}

int GenericCommunicator::recvInt(){
    string message;
    this->recvMessage(message);

    return this->extractInteger(message);
}

int GenericCommunicator::extractInteger(string e){
    size_t i=0;
    string subStr;
    size_t found=e.find("%INT%=");
    if(found != string::npos){
        while(e[i]!='='){
            ++i;
        }

        subStr=e.substr(i+1,e.size());
    }

    return atoi(subStr.c_str());
}

bool GenericCommunicator::recvBool(){
	string message;
	this->recvMessage(message);
	return message=="true";
}

Request * GenericCommunicator::recvRequest(){
    string message;
    Request * request = new Request(this);
    this->recvMessage(message);
    request->setCommands(message);
    return request;
}

void GenericCommunicator::recvRequest(Request * request){
    string message;
    this->recvMessage(message);
    request->setCommands(message);
}

