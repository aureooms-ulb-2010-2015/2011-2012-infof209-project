#include <iostream>
#include <string>
#include "GameServer.hpp"
#include "Player.hpp"
#include "Games/Ludo/LudoClass/Ludo.hpp"
#include "Games/Checkers/CheckersGame.hpp"
#include "Games/Reversi/h/Reversi.h"

#include "ListenerServer.hpp"
#include "Games/Backgammon/Backgammon.hpp"
#include "GameServer_routing.cpp"


#include "../Library/all.hpp"
#include "Bet/Bet.hpp"

using namespace std;
/*
-------------------------------------
Constructeurs
-------------------------------------
*/
GameServer::GameServer(int port,const char * ip) : Server(port, ip){
    this->setGame(NULL);
    this->setBet(NULL);
}
/*
-------------------------------------
Méthodes publiques
-------------------------------------
*/

void GameServer::initDatas(ListenerServer * listener, string nickname){
    listener->setServer(this);
    listener->init(nickname);
    listener->start();
    string message="|notFull|full|";
    this->loadGames(message);
    this->loadFriends();
    this->loadRanking();
}

void GameServer::displayMessage(Request * request){
    if(request->getName()=="friends"){
        if(request->getAttributes().size()>=2){
            cout<<"________________________________"<<endl
                <<endl
                <<request->getAttributes()[1]<<endl
                <<"________________________________"<<endl;
        }
    }
}


void GameServer::loadRanking(){
    Request request(this);
    request.makeRequest("GET","ranking");
    request.flush();
}

void GameServer::loadGames(string param){
    Request request(this);
    request.makeRequest("GET","games");
    request.addAttribute(param);
    request.flush();
}

void GameServer::loadFriends(){
    Request request(this);    
    request.makeRequest("GET","friends");
    request.flush();
}

GameInfos * GameServer::getGameInfos(int id){
    for(unsigned int i = 0; i<this->getGameList()->size();++i){
        if(this->getGameList()->at(i).getId() == id){
            return &(getGameList()->at(i));
        }
    }
    return NULL;
}

void GameServer::addGameToList(Request * request){    
    this->getGameList()->push_back(requestToGameInfos(request));
}

void GameServer::removeGameFromList(Request * request){
    GameInfos gi = this->requestToGameInfos(request);
    int i = this->findGameInfos(gi);
    if(i>=0){
        this->getGameList()->erase(this->getGameList()->begin()+i);
    }
}

void GameServer::refreshGameInfos(Request * request){
    GameInfos gi = this->requestToGameInfos(request);
    int i = this->findGameInfos(gi);
    if(i>=0){
        this->getGameList()->at(i) = gi;
    }
}

GameInfos GameServer::requestToGameInfos(Request * request){  
    string type,name;
    int id, nPlayers, maxPlayers;
    if(request->getAttributes().size()>4){
        name= request->getAttributes()[0];
        id = atoi(request->getAttributes()[1].c_str());
        type= request->getAttributes()[2];
        nPlayers = atoi(request->getAttributes()[3].c_str());
        maxPlayers= atoi(request->getAttributes()[4].c_str());
    }
    else{
        throw new IndexOutOfBoundException("Mauvais nombre d'arguments");
    }
    return GameInfos(type, name, id, nPlayers, maxPlayers);
}

int GameServer::findGameInfos(GameInfos gi){
    for(unsigned int i = 0;i <this->getGameList()->size();++i){
        if(this->getGameList()->at(i).getId() == gi.getId()){
            return i;
        }
    }
    return -1;
}

void GameServer::refreshGameList(){
    this->getGameList()->clear();
}

void GameServer::displayGameList(){
    vector<GameInfos> * games = this->getGameList();
    for(unsigned int i=0;i< games->size();++i){
        cout<< games->at(i).getId()<<"\t"
            << games->at(i).getType()<<"\t\t"
            << games->at(i).getName()<<"\t\t"
            << games->at(i).getNumberOfPlayers()<<"/"
            << games->at(i).getRequiredPlayers()<<"\t"
            <<endl;
    }
}

void GameServer::displayFriends(Request * request){
    cout<<"Your friends are : "<<endl
        <<"___________________"<<endl;
    for(unsigned int i = 0;i<request->getAttributes().size();++i){
        cout<<"\t-- "<<request->getAttributes()[i]<<endl;
    }
}

void GameServer::startGame(string type, int nPlayers, Request * request){
	Bet* bet = new Bet(this);
	this->setBet(bet);
	Game  * game; 
	if(type=="Ludo"){
	    game=new Ludo(nPlayers, this);
	}
	if (type=="Backgammon"){
		game=new Backgammon(this);
	}
	else if (type=="Dames"){
		game=new CheckersGame(this);
	}
	else if (type=="Reversi"){		
		game=new Reversi(this);
	}
	this->setGame(game);
	if(request){
	    request->flush();
	    delete(request);
	}
	while(game->running()){
	    sleep(2);
	}
	this->setGame(NULL);
	delete(game);
}

void GameServer::startChat(Request* request){

		ostringstream temp;
		temp << "gnome-terminal -e './Chat_Client_Alone ";
		temp << this->getIp() << " ";
		temp << request->getAttributes()[0] << " ";
		temp << request->getAttributes()[1] << "'";
		string cmd = temp.str();
		system(cmd.c_str());
}

void GameServer::createGame(string type, int number, string name){
	ostringstream stream;
	stream<<number;
	Request * request= new Request(this);
	request->makeRequest("CREATE_GAME",type);
	request->addAttribute(stream.str());
	request->makeRequest("SET","gameName");
	request->addAttribute(name);
	request->flush();
	this->startGame(type,number);
}

void GameServer::viewGame(string type, int number, Request * req){
    this->startGame(type, number,req);
}

void GameServer::playGame(){
	//Methode qui consiste a jouer
}

bool GameServer::isMyTurn(){
	//Méthode qui demande au serveur si c'est le tour du joueur
	Request * request= new Request(this);
	return request->getBool("myTurn");
}

void GameServer::pause(){
    Request * request= new Request(this);
	request->makeRequest("THREAD","wait");
	request->flush();
	this->recvBool();
}


int GameServer::getMyPlayerID(){
    Request * request= new Request(this);
	return request->getInt("relativePlayerId");
}

string GameServer::getLastMove(){
    Request * request= new Request(this);
	return request->get("lastMove");
}


void GameServer::sendMove(string move){
    Request * request= new Request(this);
    request->makeRequest("SET","move");
    request->addAttribute(move);
    request->flush();

}
/*
-------------------------------------
Getters
-------------------------------------
*/

Player * GameServer::getPlayer(){
	return this->_player;
}

/*
-------------------------------------
Setters
-------------------------------------
*/
void GameServer::setPlayer(Player *player){
	this->_player=player;
}

void GameServer::addPlayerToRanking(Request * request){
    Player player;
    if(request->getAttributes().size()>=2){
        player.setName(request->getAttributes()[0]);
        player.setPoints(atoi(request->getAttributes()[1].c_str()));
        this->getRanking()->push_back(player);
        this->sortVector(this->getRanking());
    }
}

void GameServer::addFriendToList(Request * request){
    Player player;
    if(request->getAttributes().size()>=2){
        player.setName(request->getAttributes()[0]);
        player.setPoints(atoi(request->getAttributes()[1].c_str()));
        this->getFriendList()->push_back(player);
        this->sortVector(this->getFriendList());
    }
}

void GameServer::removeFriendFromList(Request * request){
    Player player;
    if(request->getAttributes().size()>=1){
        for(unsigned int i = 0; i<this->getFriendList()->size();++i){
            if(this->getFriendList()->at(i).getName() == request->getAttributes()[0]){
                this->getFriendList()->erase(this->getFriendList()->begin()+i);
                break;
            }
        }
    }
}

void GameServer::sortVector(vector<Player> * v){
    Player swap;
    for(int i = v->size()-1; i>0 ;--i){
        for(int j = 0;j<i;++j){
            if(v->at(j).getPoints() < v->at(j+1).getPoints()){
                swap = v->at(j);
                v->at(j)=v->at(j+1);
                v->at(j+1)=swap;
            }
        }
    }
}

void GameServer::displayFriendList(){    
    Player player;
    cout<<"____________"<<endl
        <<endl
        <<"Liste d'amis"<<endl
        <<"____________"<<endl;
    for(unsigned int i = 0; i<this->getFriendList()->size();++i){
        player = this->getFriendList()->at(i); 
        cout<<"\t."<<"\t\t"<<player.getName()<<"\t\t"<<player.getPoints()<<" points"<<endl;
    }
}

void GameServer::displayRanking(){    
    Player player;
    cout<<"____________"<<endl
        <<endl
        <<"Ranking"<<endl
        <<"____________"<<endl;
    for(unsigned int i = 0; i<this->getRanking()->size();++i){
        player = this->getRanking()->at(i); 
        cout<<"\t."<<"\t\t"<<player.getName()<<"\t\t"<<player.getPoints()<<" points"<<endl;
    }
}
