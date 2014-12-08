#ifndef SERVERGAME
#define SERVERGAME

#include "Server.hpp"
#include <string>
#include "Ranking.hpp"

using namespace std;

class GameInstance;
class Player;

class ServerGame : public Server{
	private :
		vector<GameInstance *> _games;
		vector<Player *> _players;
		Ranking * _ranking;
	public :
		ServerGame(int);
		
		virtual void start();
		virtual void display(std::ostream &flux);
		virtual void addGame(GameInstance *);
		virtual void removeGame(GameInstance * game);
		virtual void addPlayer(Player *);
		virtual void removePlayer(Player * player);
		virtual bool isConnected(string, unsigned int);
		
		virtual void signalNewGame(GameInstance *);
		virtual void signalRemoveGame(GameInstance *);
		virtual void refreshGameInfos(GameInstance *);
		virtual void signalGameListModification(GameInstance *, const char *);
		
		//Getters
		virtual vector<GameInstance *> * getGames(){return &_games;}
		virtual vector<Player *> * getPlayers(){return &_players;}
		virtual Player * getPlayer(int i){return _players[i];}
		virtual GameInstance * getGame(int i){return _games[i];}
		virtual Ranking * getRanking(){return _ranking;}
		
		//Setters
		virtual void setRanking(Ranking * r){_ranking = r;}
};

std::ostream &operator<<(std::ostream &out, ServerGame &);
std::ostream &operator<<(std::ostream &out, ServerGame *);
#endif
