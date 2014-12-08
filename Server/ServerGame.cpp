#include<iostream>
#include<vector>
#include "ServerGame.hpp"
#include "GameInstance.hpp"
#include "Player.hpp"
#include "../Library/all.hpp"

using namespace std;

/*
____________________________________________________________________________________

Constructeurs
____________________________________________________________________________________

*/

ServerGame::ServerGame(int port) : Server(port){
	this->addGame(new GameInstance());
	this->setRanking(new Ranking("cache_Ranking/"));
}

/*
____________________________________________________________________________________

Méthodes principales
____________________________________________________________________________________

*/

void ServerGame::start(){
	int newFd;
	Player * player;
	Client * client;
	socklen_t sockAddressSize = sizeof(struct sockaddr_in);
	this->init();		//initialisation du serveur
	while(1){
		try{
			cout<<"En attente d'une nouvelles connexion"<<endl;
			newFd = accept(this->getSocket(),(struct sockaddr *)this->getClientAddress(), &sockAddressSize);
			cout<<"Nouvelle connexion recue"<<endl;
			client = new Client(newFd);
			if(client->isPlayer()){
			    player = new Player(this,newFd);
			    player->setName(client->getName());
			    player->setPassword(client->getPassword());
			    this->addPlayer(player);
			    player->start();
			}
			else{
			    for(int i=this->getPlayers()->size()-1;i>=0;--i){
			        player = this->getPlayers()->at(i);
			        if(player && player->getName()==client->getName()){
			            player->setNotifier(GenericCommunicator(newFd));
			            break;
			        }
			    }
			}
			if(newFd == -1){
				throw new ConnectionException("Le socket client est érroné !");
			}
		}
		catch(ConnectionException * e){
			e->display();
		}
	}
}

/*
____________________________________________________________________________________

Méthodes publiques
____________________________________________________________________________________

*/

void ServerGame::signalNewGame(GameInstance * gi){
    this->signalGameListModification(gi, "addGameToList");
}

void ServerGame::signalRemoveGame(GameInstance * gi){
    this->signalGameListModification(gi, "removeGameFromList");
}

void ServerGame::refreshGameInfos(GameInstance * gi){
    this->signalGameListModification(gi, "refreshGameInfos");
}

void ServerGame::signalGameListModification(GameInstance * gi, const char * type){
    Request * request;
    Player * player;
    for(unsigned int i = 0;i<this->getPlayers()->size(); ++i){
        try{
            player = this->getPlayers()->at(i);
            if(player){
                request = new Request(player->getNotifier());
                request->makeRequest("GAME_SERVER",type);
                request->addAttribute(gi->getName());
                request->addAttribute(gi->getId());
                request->addAttribute(gi->getType());
                request->addAttribute(gi->getNumberOfPlayers());
                request->addAttribute(gi->getRequiredPlayers());
                request->flush();
            }
        }catch(ConnectionException * e){}
    }
}

bool ServerGame::isConnected(string name , unsigned int id){
    Player * player;
    for(unsigned int i=0; i< this->getPlayers()->size();++i){
        player = this->getPlayers()->at(i);
        if( player && player->LOGGED &&(player->getName() == name) && (player->getId() != id) ){
            return true;
        }
    }
    return false;
}

void ServerGame::addGame(GameInstance * game){
	for(unsigned int i = 0;i<this->getGames()->size();++i){
        if(! this->getGames()->at(i)){
        	game->setId(i);
            this->getGames()->at(i) = game;
            this->signalNewGame(game);
            return;
        }
    }
	game->setId(this->getGames()->size());
	this->getGames()->push_back(game);
	this->signalNewGame(game);
}

void ServerGame::removeGame(GameInstance * game){
    this->getGames()->at(game->getId()) = NULL;
	this->signalRemoveGame(game);
}

void ServerGame::addPlayer(Player * player){
    for(unsigned int i = 0;i<this->getPlayers()->size();++i){
        if(! this->getPlayers()->at(i)){
            this->getPlayers()->at(i) = player;
            return;
        }
    }
	this->getPlayers()->push_back(player);
}

void ServerGame::removePlayer(Player * player){
    for(unsigned int i=0; i<this->getPlayers()->size();++i){
        if(this->getPlayers()->at(i) && this->getPlayers()->at(i)->getId() == player->getId()){
            this->getPlayers()->at(i)=NULL;
            return;
        }
    }
}

void ServerGame::display(std::ostream &out){
	//Méthode appelée l'ors de l'appel a cout<<
	for(unsigned int i=0; i<getGames()->size();++i){
		out<<endl<<(*this->getGames())[i];	
	}
}

/*
____________________________________________________________________________________

Surcharge des opérateurs
____________________________________________________________________________________

*/

std::ostream &operator<<(std::ostream &out, ServerGame & server){
	server.display(out);
    return out;	
}

std::ostream &operator<<(std::ostream &out, ServerGame * server){
	server->display(out);
	return out;	
}
