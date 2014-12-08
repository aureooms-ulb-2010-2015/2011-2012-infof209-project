#ifndef CLIENT_ROUTING
#define CLIENT_ROUTING

#include<iostream>
#include <fstream>
#include <stdlib.h>

#include "Client.hpp"
#include "ServerGame.hpp"

#include "../Common/GenericServer.hpp"
#include "../Library/all.hpp"



void Client::route(Request * request){
    string name=request->getName();
    string method=request->getType();
    string attribute=request->getAttributes()[0];
    if(method == "GET" || method=="get"){
		this->get(request);
	}
	else if(method == "SET" || method=="set"){
		this->set(name,attribute);
	}
	else if(method=="CREATE"||method=="create"){
		this->create(name,attribute);
	}
	else if(method=="CREATE_GAME"||method=="create"){
		this->createGame(name,attribute);
	}
	else if(method=="LOGOUT"||method=="logout"){
		throw new ConnectionException();
	}
	else if(method=="ADD"||method=="add"){
		this->add(name,attribute);
	}
	else if(method=="REMOVE" || method=="remove"){
	   this->remove(name,attribute);
	}
}

void Client::remove(string name, string attr){
    if(name == "friend"){
        this->removeFriend(this->getName(), attr);
    }
}

void Client::create(string name, string attribute){
	this->addAccountToFile(name,attribute);
	throw new ConnectionException("Compte crée");
}

void Client::add(string name,string attribute){
	Request * request;
	string message;
	if(name=="friend"){
	    request = new Request(this->getNotifier());
		if(attribute==this->getName()){
		    request->makeRequest("MESSAGE","friends");
		    request->addAttribute("false");
		    request->addAttribute("Vous ne pouvez pas vous ajouter vous meme a votre liste d'amis.");
		}
		else if(this->exists(attribute)){
			if(this->existsInFriendlist(this->getName(),attribute)){
				message=attribute;
				message+=" fait déja parti de votre liste d'amis.";
				request->makeRequest("MESSAGE","friends");
		        request->addAttribute("false");
		        request->addAttribute(message);
			}
			else{
				this->addFriend(this->getName(),attribute);
				message="L'ajout de l'ami \"";
				message+=attribute;
				message+="\" à été effectué.";
		        request->makeRequest("MESSAGE","friends");
		        request->addAttribute("true");
		        request->addAttribute(message);
			}
		}
		else{
			message="Le membre \"";
			message+=attribute;
			message+="\" n'existe pas.";
			request->makeRequest("MESSAGE","friends");
		    request->addAttribute("false");
		    request->addAttribute(message);
		}
		request->flush();
		delete(request);
	}
}

void Client::get(Request * req){
    Request * request = new Request(this->getNotifier());
    string name = req->getName();
    string attr = req->getAttributes()[0];
	string buffer = "false";
	if(name=="name"){
		if(attr=="checked"){
			if( !( ( this->exists(this->getName()) ) || (  attr.empty() ) )  ){
				buffer="true";
			}
		}
		else{
			buffer = this->getName();
		}
		this->sendMessage(buffer);
	}
	else if(name=="login"){
		if(this->login()){
		    buffer="true";
		}
		this->sendMessage(buffer);
	}
	else if(name=="friends"){
		this->getFriends(request);
	}
	else if(name=="ranking"){
	    this->loadGlobalRanking();
	}
	delete(request);
}

void Client::set(string name, string attr){
	if(name=="name"){
		this->setName(attr);
	}
	else if(name=="password"){
		this->setPassword(attr);
	}
	else if(name=="newPassword"){
		this->setNewPassword(attr);
	}
}

#endif
