#ifndef PLAYER
#define PLAYER

#include<iostream>
#include "Client.hpp"

class GameServer;
class GameInstance;

using namespace std;

class Player : public Client{
	private :
		GameInstance * _currentGame;
		int _playerId;
		int _bet;
	public :
		Player(string name, ServerGame *);
		Player(string, ServerGame *,int);
		Player(ServerGame *,int);
		
		//Publiques
		virtual void set(string,string);
		virtual void get(Request *);
		virtual void createGame(string, string);
		virtual void join(string, string);
		virtual void joinGame(unsigned int);				//Définit le jeu dont l'id est l'entier comme le jeu courrent
		virtual void joinGameAsVieuwer(unsigned int);
		virtual void * run(void *);							//Méthode appelée l'ors de l'execution du thread
		virtual void display(std::ostream &flux);			//Méthode appelée l'ors d'un cout<<
		virtual bool isMyTurn();
		virtual void route(Request *);
		virtual void bet(int);
		virtual void getGames(Request *);
		virtual void notifyActiveTurn();
		virtual void move(string);
		virtual void waitBegin();
		
		virtual void confirmBet(Request *);
		
		virtual void exitGame();
		
		//Setters
		virtual void setPlayerId(int id){_playerId=id;cout<<"SET PLAYER ID : "<<_playerId<<endl;}
		virtual void setGame(GameInstance * game){_currentGame=game;}
        
        //Getters
		virtual int getPlayerId(){return _playerId;}
		virtual int getBet(){return _bet;}
		virtual GameInstance * getGame(){return _currentGame;}
		
	private :
		virtual void wakupOthers();
};

class LostPlayerException : public Exception{
    private :
        Player * _client;
    public :
        LostPlayerException(Player * client){_client=client;}
        Player * getPlayer(){return _client;} 
};

std::ostream &operator<<(std::ostream &out, Player &);
std::ostream &operator<<(std::ostream &out, Player *);
#endif
