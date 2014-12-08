#include <iostream>
#include <sstream>
#include <string>
#include "GameServer.hpp"

#include "Games/Backgammon/Backgammon.hpp"
#include "ListenerServer.hpp"

#include "Bet/Bet.hpp"

#include "../Library/all.hpp"
#include "../Common/Request.hpp"

using namespace std;
/*
-------------------------------------
Routing
-------------------------------------
*/

void GameServer::route(Request* request){
    if(request->getType()=="GAME_SERVER"){
        if(request->getName() == "addGameToList"){
            this->addGameToList(request);
        }
        else if(request->getName() == "removeGameFromList"){
            this->removeGameFromList(request);
        }
        else if(request->getName() == "refreshGameInfos"){
            this->refreshGameInfos(request);
        }
        else if(request->getName() == "refreshGameList"){
            this->refreshGameList();
        }
        else if(request->getName() == "displayGameList"){
            this->displayGameList();
        }
        else if(request->getName() == "friends"){
            this->displayFriends(request);
        }
        else if(request->getName() == "startChat"){
			this->startChat(request);
        }
        else if(request->getName() == "addFriend"){
            this->addFriendToList(request);
        }
        else if(request->getName() == "removeFriend"){
            this->removeFriendFromList(request);
        }
        else if(request->getName() == "addPlayerToRanking"){
            this->addPlayerToRanking(request);
        }
    }
    else if(request->getType()=="MESSAGE"){
        this->displayMessage(request);
    }
    else if( request->getType()=="BET" && this->getBet()){
        this->getBet()->route(request);
    }
    else if(request->getType()=="GAME"){
        if(this->getGame()){
            this->getGame()->route(request);
        }
    }
}

void GameServer::warning(Request * request){
    cout<<"Warning : "<<request->getName()<<endl;
    for(unsigned int i=0; i<request->getAttributes().size();++i){
        cout<<"\t"<<request->getAttributes()[i]<<endl;
    }
}
