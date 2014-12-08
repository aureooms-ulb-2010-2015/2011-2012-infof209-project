#include<iostream>
#include <fstream>
#include <stdlib.h>

#include "Client.hpp"
#include "ServerGame.hpp"
#include "Client_routing.cpp"

#include "../Common/GenericServer.hpp"
#include "../Library/all.hpp"

unsigned int Client::id = 0;

/*
____________________________________________________________________________________

Constructeurs
____________________________________________________________________________________

*/

Client::Client(string name, int socket){
	this->setName(name);
	this->setSocket(socket);
	this->setNewId();
	this->LOGGED = false;
}

Client::Client(int socket){
	this->setSocket(socket);
	this->setNewId();
	this->LOGGED = false;
}

Client::Client(string name, string password) : Thread(){
	this->setName(name);
	this->setPassword(password);
	this->setNewId();
	this->LOGGED = false;
}

Client::Client(string name) : Thread(){
	this->setName(name);
	this->setNewId();
	this->LOGGED = false;
}

/*
____________________________________________________________________________________

Méthodes d'initialisation
____________________________________________________________________________________

*/

bool Client::isPlayer(){
    unsigned int size;
    Request * request = new Request(this);
    this->recvRequest(request);
    bool reponse = true;
    bool isAnAsnwer = false;
    while( (size=request->loadNextCommand()) != 0 ){
        if(request->getType()=="CONNECTION"){
            if(request->getName()=="listener"){
                this->setName(request->getAttributes()[0]);
                reponse = false;
                isAnAsnwer = true;
            }
             else if(request->getName()=="player"){
                reponse = true;
                isAnAsnwer = true;
            }
        }
        else{
            this->route(request);
        }
   }
   if(!isAnAsnwer){
        throw new ConnectionException("Probleme dans l'initialisation des sockets.");
   }
  delete(request);
  return reponse;
}

/*
____________________________________________________________________________________

Méthodes run
____________________________________________________________________________________

*/

void * Client::run(void * arg){
	Request * request = new Request(this);
	try{
		while(true){
			this->recvRequest(request);
			while(request->loadNextCommand() != 0){
			    this->route(request);
			}
		}
	}
	catch(ConnectionException * e){
		cout<<e->getMessage()<<endl;
		close(this->getSocket());
	}
	return arg;
}

/*
____________________________________________________________________________________

Méthodes de gestion des utilisateurs
____________________________________________________________________________________

*/


void Client::loadGlobalRanking(){
    Request request(this->getNotifier());
    ifstream database("cache_Clients/database.txt");
	string line;
	if(database){
		while (getline(database,line)) {
		    request.makeRequest("GAME_SERVER","addPlayerToRanking");
            request.addAttribute(line);
            request.addAttribute(this->getGameServer()->getRanking()->getPlayerPoints(line));
		    getline(database,line);
		}
		request.flush();
	}
	database.close();
}

bool Client::login(){
    bool res = true;
    if( ! this->checkPassword(this->getName(),this->getPassword()) ){
		res=false;
    }
	if( this->getName().empty() ){
	    res = false;
	}
	if(!this->getGameServer() || this->getGameServer()->isConnected(this->getName(), this->getId()) ){
	    res = false;
	}
	LOGGED = res;
	return res;
}

bool Client::exists(string nickname){
	ifstream database("cache_Clients/database.txt");
	string line;
	if(database){
		while (getline(database,line)) {
			if(nickname == line){
				database.close();
				return true;
			}
			getline(database,line); // Skipping the password.
		}
	}
	database.close();
	return false;	
}

void Client::addAccountToFile(string nickname,string password){
    if( !( nickname.empty() || password.empty() ) ){
	    ofstream database("cache_Clients/database.txt",ios::app);
	    database << nickname<<"\n"<< password<<"\n";
	    database.close();
	}
}

bool Client::checkPassword(string nickname,string password){
	ifstream database("cache_Clients/database.txt");
	string line;
	bool found = false;
	while ((not found) && (getline(database,line))){
		if(nickname == line)
			found = true;
		getline(database,line); // Skipping the password.
	}
	if (line == password)
		return true;
	else
		return false;
}

void Client::setNewPassword(string pass){
    string line;
    bool next = false;
    int i = 0;
    string const fileNameTrans = "cache_Clients/cache_database.txt";
    string const fileName = "cache_Clients/database.txt";
    ifstream friendsRead(fileName.c_str());
    if(friendsRead.is_open()){
        ofstream friendsWrite(fileNameTrans.c_str(),ios::app);
        while(getline(friendsRead, line)){
            if(( (i%2) == 0 ) && ( line == this->getName() )){
                next =true;
            }
            else if(next){
                line= pass;
                next = false;
            }
            friendsWrite<<line<<"\n";
            ++i;
        }
    friendsRead.close();
    friendsWrite.close();
    std::remove(fileName.c_str());
    std::rename(fileNameTrans.c_str(),fileName.c_str());
    }
}

/*
____________________________________________________________________________________

Méthodes de gestion d'amis
____________________________________________________________________________________

*/

bool Client::existsInFriendlist(string nickname,string friendName){
	string const fileName = "cache_Clients/" + nickname + "_friends.txt";
	ifstream database(fileName.c_str());
	string line;
	while (getline(database,line)) {
		if(friendName == line)
			return true;
	}
	database.close();
	return false;	
}

void Client::addFriend(string user, string friendName){
    Request request(this->getNotifier());
    request.makeRequest("GAME_SERVER","addFriend");
    request.addAttribute(friendName);
    request.addAttribute(this->getGameServer()->getRanking()->getPlayerPoints(friendName));
    request.flush();
	string const fileName = "cache_Clients/" + user + "_friends.txt";
	ofstream friends(fileName.c_str(),ios::app);
	friends << friendName << "\n";
	friends.close();
}

void Client::removeFriend(string user, string friendName){
    string line;
    string const fileNameTrans = "cache_Clients/" + user + "_friends_transfert.txt";
    string const fileName = "cache_Clients/" + user + "_friends.txt";
    ifstream friendsRead(fileName.c_str());
    if(friendsRead.is_open()){
        ofstream friendsWrite(fileNameTrans.c_str(),ios::app);
        while(getline(friendsRead, line)){
            if(line != friendName){
                friendsWrite<<line<<"\n";
                Request request(this->getNotifier());
                request.makeRequest("GAME_SERVER","removeFriend");
                request.addAttribute(friendName);
                request.flush();
            }
        }
    friendsRead.close();
    friendsWrite.close();
    std::remove(fileName.c_str());
    std::rename(fileNameTrans.c_str(),fileName.c_str());
    }
}

void Client::getFriends(Request * request){
	string const fileName = "cache_Clients/" + this->getName() + "_friends.txt";
	ifstream database(fileName.c_str());
	string line;
	while (getline(database,line)) {
        request->makeRequest("GAME_SERVER","addFriend");
        request->addAttribute(line);
        request->addAttribute(this->getGameServer()->getRanking()->getPlayerPoints(line));
	}
	request->flush();
	database.close();
}

/*
____________________________________________________________________________________

Autres méthodes non classables
____________________________________________________________________________________

*/

void Client::display(std::ostream &out){
	out<<this->getName();
}

/*
____________________________________________________________________________________

Getters
____________________________________________________________________________________

*/

unsigned int Client::getNewId(){
	return Client::id++;
}

/*
____________________________________________________________________________________

Setters
____________________________________________________________________________________

*/

void Client::setNewId(){
	this->_id=Client::getNewId();
}

/*
____________________________________________________________________________________

Surcharge des opérateurs
____________________________________________________________________________________

*/

std::ostream &operator<<(std::ostream &out, Client & client){
	client.display(out);
    return out;	
}

std::ostream &operator<<(std::ostream &out, Client * client){
	client->display(out);
	return out;	
}
