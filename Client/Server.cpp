#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include<fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string>

#include "../Library/all.hpp"
#include "../Common/Request.hpp"
#include "ListenerServer.hpp"
#include "Server.hpp"

using namespace std;

/*
____________________________________________________________________________________

Constructeurs
____________________________________________________________________________________

*/

Server::Server(int port,const char * ip){
	this->setPort(port);
	this->setIp(ip);
}

void Server::init(){
	this->initClientSocket();

	if(connect(this->getSocket(), (struct sockaddr *)this->getServerAddress(), sizeof(struct sockaddr_in)) == -1){
		throw new ConnectionException();
	}
}

void Server::initClientSocket(){
	//initialisation d'un socket du coté client
	//vers un serveur
	struct hostent *serverInfo;
	int sockFd;
	if((serverInfo=gethostbyname(this->getIp())) == NULL){ 
		throw new ConnectionException();
	}
	if((sockFd = socket(PF_INET, SOCK_STREAM, 0)) == -1){
		throw new ConnectionException();
	}
	this->setSocket(sockFd);
	this->getServerAddress()->sin_family = AF_INET;
	this->getServerAddress()->sin_port = htons(this->getPort());
	this->getServerAddress()->sin_addr = *((struct in_addr*)serverInfo->h_addr);
	memset(&(this->getServerAddress()->sin_zero),'\0', 8);
}

const char * Server::getIp(){
	return this->_ip;
}

void Server::setIp(const char * ip){
	this->_ip= ip;
}

void Server::login(string nick, string pass){
    Request * request = new Request(this);
	this->init();
	bool b=false;
	request->makeRequest("CONNECTION","player");
    request->flush();
	request->set("name",nick);
	this->setName(nick);
	request->set("password",pass);
	b=request->getBool("login");
	if(b){
		cout<<"Vous etes a présent connecté"<<endl;
		this->_logged = true;
	}
	else{
	    close(this->getSocket());
	}
}

void Server::logout(){
	string message="LOGOUT:::;";
	this->sendMessage(message);
	close(this->getSocket());
	this->_logged=false;
}

void Server::createAccount(string name, string pass){
    Request * request = new Request(this);
	bool b = false;
	this->init();
	request->makeRequest("CONNECTION","player");
    request->flush();
	request->set("name",name);
	this->setName(name);
	b=request->getBool("name","checked");
	if(b){
	    request->makeRequest("CREATE",name);
	    request->addAttribute(pass);
	    request->flush();
	}
}

Player * Server::getPlayer(){
	return this->_player;
}

void Server::setPlayer(Player *player){
	this->_player=player;
}

bool Server::isLogged(){
	return this->_logged;
}

string Server::getName(){
	return this->_name;
}
void Server::setName(string name){
	this->_name=name;
}
/*

SEND

*/

void Server::sendName(string name){
    string message="SET:name:"+name+":;";
    this->sendMessage(message);
}

