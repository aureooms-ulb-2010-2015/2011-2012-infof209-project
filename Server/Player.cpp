#include <iostream>
#include "../Library/all.hpp"

#include "Player.hpp"
#include "GameInstance.hpp"
#include "ServerGame.hpp"
#include "Server.hpp"
#include "../Common/Request.hpp"
#include "Player_routing.cpp"

using namespace std;
/*
____________________________________________________________________________________

Constructeurs
____________________________________________________________________________________

*/

Player::Player(string name, ServerGame * server) : Client(name){
	this->setGameServer(server);
	this->setGame(NULL);
	this->_bet=0;
}

Player::Player(string name, ServerGame * server, int socket) : Client(name,socket){
	this->setGameServer(server);
	this->setGame(NULL);
	this->_bet=0;
}

Player::Player(ServerGame * server, int socket) : Client(socket){
	this->setGameServer(server);
	this->setGame(NULL);
	this->_bet=0;
}
/*
____________________________________________________________________________________

Methodes run
____________________________________________________________________________________

*/

void * Player::run(void * arg){
    Request * request = new Request(this);
    unsigned long int k = 0;
    try{
    	try{
		    while(true){
			    this->recvRequest(request);
			    while(request->loadNextCommand() != 0){
			        if(this->getName().size() != 0){
			            cout<<"Request "<<k<<" from member <"<<this->getName()<<"> : ["<<"Type = \""<<request->getType()<<"\" Name = \""<<request->getName()<<"\"]"<<endl;
		            }
		            else{
		                cout<<"Request : ["<<"Type = \""<<request->getType()<<"\" Name = \""<<request->getName()<<"\"]"<<endl;
		            }
		            if(request->getAttributes().size()>0){
		                cout<<"\tAttributes : [\""<<request->getAttributes()[0]<<"\"";
		            }
		            for(unsigned int i=1;i<request->getAttributes().size();++i){
		                cout<<", \""<<request->getAttributes()[i]<<"\"";
		            }
		            cout<<"]"<<endl;
			        this->route(request);
			        cout<<"Request "<<k<< " for member "<<this->getName()<<" is done."<<endl;
			        ++k;
			    }
		    }
	    }
	    catch(ConnectionException * e){
		    this->exitGame();
		    delete(request);
		    throw new LostPlayerException(this);
	    }
	}
	catch(LostPlayerException * e){
		    close(e->getPlayer()->getSocket());
		    if(e->getPlayer()->getGame()){
		        e->getPlayer()->getGame()->removePlayer(this);
		    }
		    this->getGameServer()->removePlayer(e->getPlayer());
	}
	return arg;
}

/*
____________________________________________________________________________________

Methodes de Gestion des jeux
____________________________________________________________________________________

*/

void Player::exitGame(){
    if(this->getGame()){
	    this->getGame()->removePlayer(this);
    }
}

void Player::createGame(string name, string attr){
	string message;
	int i;
	GameInstance * game;
	Request * notif = new Request(this->getNotifier());
	if(name!=""){
		i=atoi(attr.c_str());
		if(i && i<=8 && i>1){
			game=new GameInstance(i,this->getGameServer());
			this->getGameServer()->addGame(game);
			this->setGame(game);
			game->setType(name);
			game->addPlayer(this);
		notif->makeRequest("GAME","setId");
		notif->addAttribute(this->getPlayerId());
		notif->flush();
		this->waitBegin();
		notif->makeRequest("GAME_SERVER","startChat");
		notif->addAttribute(this->getName());
		notif->addAttribute(this->getGame()->getGlobalId());
		notif->flush();
		}
		else{
			notif->makeRequest("ERROR","numberOfPlayers");
			notif->flush();
		}
	}
	else{
		notif->makeRequest("ERROR","gameName");
		notif->flush();
	}
	delete(notif);
}

void Player::waitBegin(){
    Request * notif;
    Player * player;
    for(unsigned int i = 0; i<this->getGame()->getPlayers()->size();++i){
	    player = this->getGame()->getPlayers()->at(i);
	    notif = new Request(player->getNotifier());
	    notif->makeRequest("GAME","setConnectedPlayers");
	    notif->addAttribute(this->getGame()->getNumberOfPlayers());
	    notif->makeRequest("GAME","waitForBegin");
	    notif->flush();
	    delete(notif);
	}
}

void Player::joinGame(unsigned int gameId){
    Request * notif =new Request(this->getNotifier());
	if(gameId<=0 || gameId >= this->getGameServer()->getGames()->size()){
	    notif->makeRequest("ERROR","gameId");
	    notif->flush();
	}
	this->setGame(this->getGameServer()->getGame(gameId));
	this->getGame()->addPlayer(this);
	notif->makeRequest("GAME","setId");
	notif->addAttribute(this->getPlayerId());
	notif->flush();
	this->waitBegin();
	notif->makeRequest("GAME_SERVER","startChat");
	notif->addAttribute(this->getName());
	notif->addAttribute(this->getGame()->getGlobalId());
	notif->flush();
	if(this->getGame()->isFull()){
	    this->getGame()->signalNoContract();
	}
	delete(notif);
}

void Player::confirmBet(Request * request){
    if(request->getAttributes().size() >0 && this->getGame()){
        if(request->getAttributes()[0] == "true"){
            this->getGame()->signContract();
        }
        else{
            this->getGame()->refuseContract();
        }
        if(this->getGame()->allrespondedToContract()){
            if(this->getGame()->betContract()){
				this->getGame()->setIsBusy(true);
                this->wakupOthers();
                this->getGame()->activateBets();
            }
            else{
                this->getGame()->signalNoContract();
            }
        }
    }
}

void Player::joinGameAsVieuwer(unsigned int gameId){
    Request * notif = new Request(this->getNotifier());
    if(gameId<=0 || gameId >= this->getGameServer()->getGames()->size()){
	    notif->makeRequest("ERROR","gameId");
	    notif->flush();
	}
	this->setGame(this->getGameServer()->getGame(gameId));
	this->getGame()->addViewer(this);
	notif->makeRequest("GAME","setId");
	notif->addAttribute(-1);
	notif->makeRequest("GAME","setConnectedPlayers");
	notif->addAttribute(this->getGame()->getNumberOfPlayers());
    notif->makeRequest("GAME","setCurrentPlayerId");
    notif->addAttribute(this->getGame()->getTurn());
	notif->makeRequest("GAME","waitForBegin");
	notif->flush();
    for(unsigned int i = 0; i<this->getGame()->getMoves()->size();++i){
	    notif->makeRequest("GAME","refresh");
        notif->addAttribute(this->getGame()->getMoves()->at(i));
    }
	notif->flush();
	delete(notif);
}

/*
____________________________________________________________________________________

Methodes appelées par les jeux
____________________________________________________________________________________

*/

void Player::move(string attr){
    Request * notify;
    Player * player;
    this->getGame()->addMove(attr);
	for(int i = 0; i<this->getGame()->getNumberOfPlayers();++i){
	    player = this->getGame()->getPlayer(i);
	     if(player->getId() != this->getId()){
		     notify = new Request(player->getNotifier());
		     notify->makeRequest("GAME","refresh");
		     notify->addAttribute(this->getGame()->getLastMove());
		     notify->flush();
		     delete(notify);
		 }
	}
	for(unsigned int i = 0; i<this->getGame()->getViewers()->size();++i){
		 player = this->getGame()->getViewers()->at(i);
	     notify = new Request(player->getNotifier());
	     notify->makeRequest("GAME","refresh");
	     notify->addAttribute(this->getGame()->getLastMove());
	     notify->flush();
	     delete(notify);
	}
}

void Player::notifyActiveTurn(){
    Player * player= this->getGame()->getPlayer(this->getGame()->getTurn());
    Request * notify = new Request(player->getNotifier());
    notify->makeRequest("GAME","setCurrentPlayerId");
    notify->addAttribute(this->getGame()->getTurn());
    notify->makeRequest("GAME","runActiveTurn");
    notify->flush();
}

void Player::wakupOthers(){
	Request * notify;
	for(int i = 0; i<this->getGame()->getNumberOfPlayers();++i){
		 notify = new Request(this->getGame()->getPlayers()->at(i)->getNotifier());
		 notify->makeRequest("GAME","display");
		 notify->makeRequest("GAME","setCurrentPlayerId");
         notify->addAttribute(this->getGame()->getTurn());
		 notify->flush();
		 delete(notify);
	}
	for(unsigned int i = 0; i<this->getGame()->getViewers()->size();++i){
		notify = new Request(this->getGame()->getViewers()->at(i)->getNotifier());
		notify->makeRequest("GAME","display");
		notify->makeRequest("GAME","setCurrentPlayerId");
		notify->flush();
		delete(notify);
	}
	this->notifyActiveTurn();
}

void Player::bet(int bet){
    Player * player;
    Request * request;
    int points=this->getGame()->getServer()->getRanking()->getPlayerPoints(this->getName());
    if(points<bet){
        bet=points;
    }
    this->_bet = bet;
    this->getGame()->addToTotalPoints(bet);
    for(unsigned int i =0;i<this->getGame()->getPlayers()->size();++i){
        player = this->getGame()->getPlayers()->at(i);
        if(player){
            cout<<"PARIS : "<<player->getName()<<player->getBet()<<endl;
            request = new Request(player->getNotifier());
            request->makeRequest("BET", "addBet");
            request->addAttribute(this->getName());
            request->addAttribute(bet);
            if(this->getGame()->allHaveBet()){
                request->makeRequest("BET","validate");
            }
            request->flush();
            delete(request);
        }
       cout<<"PARIS FIN: "<<player->getName()<<player->getBet()<<endl;
    }
}

bool Player::isMyTurn(){
	return this->getGame()->isTurn(this);
}

/*
____________________________________________________________________________________

Autres methodes non classables
____________________________________________________________________________________

*/

void Player::getGames(Request * request){
    vector<string> attrs = request->getAttributes();
    Request * req = new Request(this->getNotifier());
    req->makeRequest("GAME_SERVER","refreshGameList");
    bool done = false;
    if(attrs.size() > 0){
        vector<GameInstance *> games=(*this->getGameServer()->getGames());
	    for(unsigned int i=1; i<games.size();++i){
		    if(attrs[0].find("full")!=string::npos){
			    done=games[i]->isFull();
		    }
		    if(!done && attrs[0].find("notFull")!=string::npos){
			    done=!games[i]->isFull();
		    }
		    if(!done && attrs[0].find("type")){
		        if(attrs.size() >1){
		            done = ( attrs[1] == games[i]->getType() );
		        }
		    }
		    if(done){
                req->makeRequest("GAME_SERVER","addGameToList");
                req->addAttribute(games[i]->getName());
                req->addAttribute(games[i]->getId());
                req->addAttribute(games[i]->getType());
                req->addAttribute(games[i]->getNumberOfPlayers());
                req->addAttribute(games[i]->getRequiredPlayers());
                
			}
	    done=false;
	    } 
    }
    req->flush();
    delete(req);
}

void Player::display(std::ostream &flux){
	flux<<"Player : "<<this->getName();
}

/*
____________________________________________________________________________________

Online getters
____________________________________________________________________________________

*/



/*
____________________________________________________________________________________

Surcharge des opérateurs
____________________________________________________________________________________

*/

std::ostream &operator<<(std::ostream &out, Player & player){
	player.display(out);
    return out;	
}

std::ostream &operator<<(std::ostream &out, Player * player){
	player->display(out);
	return out;	
}
