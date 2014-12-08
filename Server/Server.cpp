#include <iostream>

#include "Server.hpp"
#include "Client.hpp"
#include "../Library/all.hpp"

#define BACKLOG 2000

using namespace std;

/*
____________________________________________________________________________________

Constructeurs
____________________________________________________________________________________

*/

Server::Server(int port){
	this->setPort(port);
}

/*
____________________________________________________________________________________

Méthodes d'initialisation
____________________________________________________________________________________

*/

void Server::init(){
	//Fonction d'initialisation du serveur
	//Afin qu'il soit pret à acceuillir des clients
	this->initClientSocket();
	if (bind(this->getSocket(), (struct sockaddr *)getServerAddress(), sizeof(struct sockaddr)) == -1){
		perror("Serveur: bind");
		throw new ConnectionException();
	}
	if(listen(this->getSocket(), BACKLOG) == -1){
		perror("Serveur: listen");
		throw new ConnectionException();
	}
}

void Server::initClientSocket(){
	//Initilaisation du socket vers le client
	int option=1;
	this->setSocket(socket(PF_INET, SOCK_STREAM, 0));
	if(setsockopt(this->getSocket(),SOL_SOCKET,SO_REUSEADDR,&option,sizeof(int)) == -1) {
	}    
	this->getServerAddress()->sin_family = AF_INET;         
	this->getServerAddress()->sin_port = htons(this->getPort());     
	this->getServerAddress()->sin_addr.s_addr = INADDR_ANY;
	memset(&(this->getServerAddress()->sin_zero), '\0', 8);
}

/*
____________________________________________________________________________________

Méthodes principales
____________________________________________________________________________________

*/

void Server::start(){
	int newFd;
	Client * client;
	socklen_t sockAddressSize = sizeof(struct sockaddr_in);
	this->init();		//initialisation du serveur
	while(1){
		try{
			cout<<"En attente d'une nouvelles connexion"<<endl;
			newFd = accept(this->getSocket(),(struct sockaddr *)this->getClientAddress(), &sockAddressSize);
			cout<<"Nouvelle connexion recue"<<endl;
			client = new Client(newFd);
			client->start();
			if(newFd == -1){
				throw new ConnectionException();
			}
		}
		catch(ConnectionException * e){
			cout<<e->getMessage()<<endl;
		}
	}
}
