#include<iostream>
#include <string>
#include <fstream>
#include <vector>
#include "GameInstance.hpp"
#include "ServerGame.hpp"
#include "Player.hpp"
#include "../Library/all.hpp"

/*
____________________________________________________________________________________

Constructeurs
____________________________________________________________________________________

*/

int GameInstance::id=0;

GameInstance::GameInstance(int maxPlayers, ServerGame * server){
	this->_playersRequired = maxPlayers;
	this->_globalId = this->id++;
	this->setTurn(0);
	this->setServer(server);
	this->_winner=NULL;
    this->initBetContract();
    this->_busy = false;
}

GameInstance::GameInstance(){
    this->_winner=NULL;
    this->setTurn(0);
	this->_globalId = this->id++;
    this->initBetContract();
    this->_busy = false;
}

/*
____________________________________________________________________________________

Méthodes Booleenes
____________________________________________________________________________________

*/

bool GameInstance::isTurn(Player * player){
	return this->isTurn(player->getPlayerId());
}

bool GameInstance::isTurn(int playerId){
	if(playerId<0){
	    return false;
	}
	if(playerId > (this->getRequiredPlayers()-1)){
	    cout<<"Incorrect player id used -> "<< playerId<<endl;
	    throw new ConnectionException();
	}
	return  (this->isFull()) && (playerId == this->getPlayer(this->getTurn())->getPlayerId());
}

bool GameInstance::isFull(){
	return (this->getNumberOfPlayers() == this->getRequiredPlayers());
}

/*
____________________________________________________________________________________

Getters
____________________________________________________________________________________

*/

int GameInstance::getNumberOfPlayers(){
	return this->getPlayers()->size();
}

int GameInstance::getNumberOfViewers(){
	return this->getViewers()->size();
}

string GameInstance::getLastMove(){
	if(this->getMoves()->empty()){
	    return "!!!";
	}
	return this->getMoves()->at(this->getMoves()->size()-1);
}

Player * GameInstance::getPlayer(int playerId){
    return this->getPlayers()->at(playerId);
}

/*
____________________________________________________________________________________

Setters et adders
____________________________________________________________________________________

*/

void GameInstance::setNextTurn(){
	if((this->getTurn()+1)==this->getRequiredPlayers()){
		this->setTurn(0);
	}
	else{
		this->setTurn(this->getTurn()+1);
	}
}

void GameInstance::addMove(string move){
    this->getMoves()->push_back(move);
}

void GameInstance::addPlayer(Player * player){
	if(this->isFull()){
		throw new IndexOutOfBoundException();		//Exception lancée lorsque le nombre de joueurs maximum est déja atteint.(Au cas ou mais ne devrai pas se produire)
	}
	this->getPlayers()->push_back(player);
	player->setPlayerId(this->getNumberOfPlayers()-1);
	this->getServer()->refreshGameInfos(this);
}

void GameInstance::addViewer(Player * viewer){
	this->getViewers()->push_back(viewer);
	viewer->setPlayerId(-1);
}

/*
____________________________________________________________________________________

Autres méthodes non classables
____________________________________________________________________________________

*/

void GameInstance::endOfGame(){
    Player * player;
    Request * request;
    for(unsigned int i=0; i<this->getPlayers()->size();++i){
        player = this->getPlayers()->at(i);
        if(player){
            request = new Request(player->getNotifier());
            request->makeRequest("GAME","endOfGame");
            request->flush();
            delete(request);
        }
    }
}

void GameInstance::signalNoContract(){
    Player * player;
    Request * request;
    for(unsigned int i=0; i<this->getPlayers()->size();++i){
        player = this->getPlayers()->at(i);
        if(player){
            this->initBetContract();
            cout<<"Contrat annulé : "<<player->getName()<<player->getBet()<<endl;
            request = new Request(player->getNotifier());
            request->makeRequest("BET","askAmount");
            request->flush();
            delete(request);
        }
    }
}

void GameInstance::activateBets(){
    Player * player;
    for(unsigned int i=0; i<this->getPlayers()->size();++i){
        player = this->getPlayers()->at(i);
        if(player){
            cout<<"A PARIS: "<<player->getName()<<player->getBet()<<endl;
            this->getServer()->getRanking()->subtractPointsToPlayer(player->getName() , player->getBet());
        }
        cout<<"A PARIS FIN: "<<player->getName()<<player->getBet()<<endl;
    }
}

void GameInstance::removePlayer(Player * player){
	for(unsigned int i=0;i<this->getPlayers()->size();++i){
		if(this->getPlayers()->at(i)->getId()==player->getId()){
			this->getPlayers()->erase(this->getPlayers()->begin()+i);
	        this->getServer()->refreshGameInfos(this);
			if(this->getPlayers()->empty()){
			   this->getServer()->removeGame(this);
	        }
	        else if(this->isBusy()){
				// SI UN JOUEUR SE DECONNECTE ET QUE LE JEU EST LANCÉ
			}
		break;
		}
	}
}

void GameInstance::display(std::ostream &out){
	//Méthode appelée lors d'un cout<<
	out<<"Jeux "<<this->getType()<<" : "<<this->getNumberOfPlayers()<<"/"<<this->getRequiredPlayers()<<" joueurs";
	for(int i=0; i<this->getNumberOfPlayers();++i){
		out<<endl<<"\t"<<(*this->getPlayers())[i];	
	}
}

/*
____________________________________________________________________________________

Surcharge des opérateurs
____________________________________________________________________________________

*/

std::ostream &operator<<(std::ostream &out, GameInstance & game){
	game.display(out);
    return out;	
}

std::ostream &operator<<(std::ostream &out, GameInstance * game){
	game->display(out);
	return out;	
}
