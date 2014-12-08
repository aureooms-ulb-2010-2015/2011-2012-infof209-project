#ifndef GAME_SERVER
#define GAME_SERVER

#include "Server.hpp"
#include "GameInfos.hpp"
#include "Player.hpp"
#include "Games/Game.hpp"

#include "../Common/Request.hpp"

class ListenerServer;
class Bet;

class GameServer : public Server{
private :
		Player * _player;
		vector<GameInfos> _gameList;
		vector<Player> _friendList;
		vector<Player> _globalRanking;
		Game * _game;
		Bet * _bet;
		
public :
		GameServer(int ,const char *);
		
		
		virtual void initDatas(ListenerServer *, string);
		virtual void startGame(string,int, Request * req = NULL);
		virtual void startChat(Request*);
		virtual void createGame(string, int, string);
		virtual void viewGame(string, int, Request *);
		virtual void playGame();
		virtual bool isMyTurn();
		virtual int getMyPlayerID();
		virtual string getLastMove();
		virtual void sendMove(string);
		virtual void pause();
        	virtual void sortVector(vector<Player> *);
		
		//Getters
		virtual Player * getPlayer();
		virtual void setPlayer(Player *);
		virtual void setGame(Game* game){_game = game;}
		virtual Game* getGame(){return _game;}
		virtual void loadGames(string); 
		virtual void loadFriends();
		virtual void loadRanking();
		virtual vector<GameInfos> * getGameList(){return &_gameList;}
		virtual vector<Player> * getFriendList(){return &_friendList;}
		virtual vector<Player> * getRanking(){return & _globalRanking;}
		virtual GameInfos * getGameInfos(int i);
		virtual Bet* getBet(){return _bet;}
		
		//Setters
		virtual void displayMessage(Request *);
		virtual void setBet(Bet * bet){_bet = bet;}
		
		//adders
		virtual void addPlayerToRanking(Request *);
		virtual void addFriendToList(Request *);
		virtual void addGameToList(Request *);
		
		virtual void removeFriendFromList(Request *);
		
		//Displayers
		virtual void displayFriendList();
		virtual void displayGameList();
		virtual void displayRanking();
		virtual void displayFriends(Request *);
		
		virtual void refreshGameList();
		virtual void removeGameFromList(Request *);
		virtual void refreshGameInfos(Request *);
		virtual GameInfos requestToGameInfos(Request *);
		virtual int findGameInfos(GameInfos);
		
		virtual void route(Request *);
		virtual void warning(Request *);
};

#endif
