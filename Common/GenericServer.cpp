#include <iostream>

#include "GenericServer.hpp"
#include "../Library/all.hpp"

#define BUFFER_LENGTH 64

using namespace std;

struct sockaddr_in * GenericServer::getServerAddress(){
	return &this->_serverAddress;
}

int GenericServer::getPort(){
	return this->_port;
}

void GenericServer::setPort(int port){
	this->_port = port;
}

