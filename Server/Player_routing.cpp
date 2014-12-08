#ifndef PLAYER_ROUTING
#define PLAYER_ROUTING


#include <iostream>
#include "../Library/all.hpp"

#include "Player.hpp"
#include "GameInstance.hpp"
#include "ServerGame.hpp"
#include "Server.hpp"
#include "../Common/Request.hpp"

using namespace std;

/*
____________________________________________________________________________________

Méthode Route 
____________________________________________________________________________________

*/

void Player::route(Request * request){
    string name=request->getName();
    string method=request->getType();
    string attribute=request->getAttributes()[0];
    if(method == "BET" || method=="bet"){
        if(name == "validate"){
            this->confirmBet(request);
        }
        else{
		    this->bet(atoi(name.c_str()));
		}
	}
	else if(method=="CREATE_GAME"||method=="create"){
		this->createGame(name,attribute);
	}
	else if(method=="GIVE"||method=="give"){
		if(name=="points"){
		    if(request->getAttributes().size() >1){
		        this->getGameServer()->getRanking()->addPointsToPlayer(request->getAttributes()[0],atoi(request->getAttributes()[1].c_str()));
		        this->getGameServer()->getRanking()->subtractPointsToPlayer(this->getName(),atoi(request->getAttributes()[1].c_str()));
		    }
		}
	}
	else if(method=="THREAD"||method=="thread"){
		if(name=="wait"){
		    try{
	           this->wait();
	        }catch(InteruptedException * e){}
	        string message="true";
	        this->sendMessage(message);
	    }
	    else if(name=="notify"){
		    this->wakupOthers();
	    }
	}
	else if(method=="JOIN" || method=="join"){
		this->join(name,attribute);
	}
	else{
	   Client::route(request);
	}
	
}

/*
____________________________________________________________________________________

Méthode GET 
____________________________________________________________________________________

*/

void Player::get(Request * req){
    string name = req->getName();
    string attr = req->getAttributes()[0];
	Request * request = new Request(this);
	string message;
	ostringstream strStream;
	vector<GameInstance *> games;
	if(name=="games"){
	    this->getGames(req);
	}
	else if(name=="game"){
	    if(!(this->getGame())){throw new ConnectionException("Game don' exist.");}
	    if(attr=="nPlayers"){
	        this->sendInt(this->getGame()->getRequiredPlayers());
	    }
	    else if(attr=="type"){
	        message=this->getGame()->getType();
	        this->sendMessage(message);
	    }
	}
	else if(name=="myTurn"){
	    if(!(this->getGame())){throw new ConnectionException("Game don' exist.");}
		if(this->isMyTurn()){
			message="true";
		}
		else{
			message="false";
		}
		this->sendMessage(message);
	}
	else if(name=="relativePlayerId"){
	    this->sendInt(this->getPlayerId());
	}
	else if(name=="currentPlayerId"){
	    this->sendInt(this->getGame()->getTurn());
	}
	else if(name=="lastMove"){
	    if(!(this->getGame())){throw new ConnectionException("Game don' exist.");}
	    message=this->getGame()->getLastMove();
	    this->sendMessage(message);
	}
	else if(name=="moves"){
	    for(unsigned int i = 0; i<this->getGame()->getMoves()->size();++i){
	        request->makeRequest("MOVE","instance");
	        request->addAttribute(this->getGame()->getMoves()->at(i));
	    }
	    request->flush();
	}
	else if(name=="numberOfPlayers"){
	    this->sendInt(this->getGame()->getNumberOfPlayers());
	}
	else if(name=="numberOfViewers"){
	    this->sendInt(this->getGame()->getViewers()->size());
	}
	else if(name=="gameStarted"){
	    this->sendBool(this->getGame()->isFull());
	}
	else if(name=="playerPoints"){
	    this->getGameServer()->getRanking()->addPlayer(this->getName());
	    strStream<<this->getGameServer()->getRanking()->getPlayerPoints(this->getName());
	    message = strStream.str();
	    this->sendMessage(message);
	}
	else if(name=="playersInGame"){
	    request->makeRequest("GAME","playersNames");
	    for(int i = 0; i<this->getGame()->getNumberOfPlayers();++i){
	        request->addAttribute(this->getGame()->getPlayer(i)->getName());
	    }
	    request->flush();
	}
	else{
	    Client::get(req);
	}
}

/*
____________________________________________________________________________________

Méthode SET 
____________________________________________________________________________________

*/

void Player::set(string name, string attr){
    ostringstream strStream;
    if(this->getGame()){
	    if(name=="gameName"){
		    this->getGame()->setName(attr);
	    }
	    else if(name=="nextTurn"){
		    this->getGame()->setTurn(atoi(attr.c_str())%this->getGame()->getRequiredPlayers());
		    Request * notif;
		    for(int i = 0; i<this->getGame()->getNumberOfPlayers();++i){
		        notif = new Request(this->getGame()->getPlayers()->at(i)->getNotifier());
                notif->makeRequest("GAME","setCurrentPlayerId");
                notif->addAttribute(this->getGame()->getTurn());
		        notif->makeRequest("GAME","display");
		        notif->flush();
		        delete(notif);
		    }
		    for(unsigned int i = 0; i<this->getGame()->getViewers()->size();++i){
		        notif = new Request(this->getGame()->getViewers()->at(i)->getNotifier());
                notif->makeRequest("GAME","setCurrentPlayerId");
                notif->addAttribute(this->getGame()->getTurn());
		        notif->makeRequest("GAME","display");
		        notif->flush();
		    }
		    this->notifyActiveTurn();
	    }
	    else if(name=="endTurn"){
		    this->wakupOthers();
	    }
	    else if(name=="quitGame"){
	        this->exitGame();
	    }
	    else if(name=="move"){
	        this->move(attr);
		    Request * notif;
	        for(int i = 0; i<this->getGame()->getNumberOfPlayers();++i){
		        notif = new Request(this->getGame()->getPlayers()->at(i)->getNotifier());
                notif->makeRequest("GAME","setCurrentPlayerId");
                notif->addAttribute(this->getGame()->getTurn());
		        notif->makeRequest("GAME","display");
		        notif->flush();
		        delete(notif);
		    }
		    for(unsigned int i = 0; i<this->getGame()->getViewers()->size();++i){
		        notif = new Request(this->getGame()->getViewers()->at(i)->getNotifier());
                notif->makeRequest("GAME","setCurrentPlayerId");
                notif->addAttribute(this->getGame()->getTurn());
		        notif->makeRequest("GAME","display");
		        notif->flush();
		    }
	    }
	    else if(name=="nextPlayer"){
	        if(!this->getGame()->getWinner()){
	            this->getGame()->setTurn(atoi(attr.c_str()));
	        }
	    }
	    else if(name=="winner"){
	        if(this->getGame()){
	            this->getGame()->setWinner(atoi(attr.c_str()));
	            this->getGameServer()->getRanking()->addPointsToPlayer(this->getGame()->getPlayer(atoi(attr.c_str()))->getName(), this->getGame()->getTotalPoints());
	            this->getGame()->endOfGame();
	        }
	    }
	}
	else{
		Client::set(name,attr);
	}
}

/*
____________________________________________________________________________________

Autres Méthodes 
____________________________________________________________________________________

*/

void Player::join(string name, string attribute){
	int i;
	if(name=="player"){
		i=atoi(attribute.c_str());
		if(i){
			this->joinGame(i);
		}
	}
	else if(name=="viewer"){
		i=atoi(attribute.c_str());
		if(i){
			this->joinGameAsVieuwer(i);
		}
	}
}
#endif
