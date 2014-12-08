#include "ListenerServer.hpp"
#include "../Common/Request.hpp"
#include <iostream>

using namespace std;

ListenerServer::ListenerServer(int port, const char * ip) : Server(port , ip){
}

void ListenerServer::init(string name){
    Server::init();
    Request * request = new Request(this);
    request->makeRequest("CONNECTION","listener");
    request->addAttribute(name);
    request->flush();
}

void * ListenerServer::run(void * arg){
    Request * request = new Request(this);
	try{
		while(true){
		    this->recvRequest(request);
			while(request->loadNextCommand() != 0){
			    this->getServer()->route(request);
			}
		}
	}
	catch(ConnectionException * e){
	}
	return arg;
}
