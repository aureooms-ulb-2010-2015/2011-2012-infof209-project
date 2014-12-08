#ifndef DEF_GAME
#define DEF_GAME

#include "../../Common/Request.hpp"

#include "GamePlayer.hpp"
#include "Board.hpp"

#include <string>
#include <sstream>

class Move;
class GameServer;

class Game{

private:
	GameServer* _server;
	Request* _request;
	int _id;
	unsigned int _numberOfPlayers;

	Board* _board;
	vector<GamePlayer*>* _players;

	unsigned int _connectedPlayers;

	bool _running;
	unsigned short int _currentPlayerId;
	
public:

	static const short int VIEWER_ID;
	static const short int NO_WINNER;

	Game(GameServer*,unsigned int,Board*);
	virtual ~Game(){}
	
	virtual GameServer* server();
	virtual void server(GameServer*);
	virtual int id();
	virtual void id(int);
	virtual int getRequiredPlayers();
	virtual Request* request();
	virtual Board* board();
	virtual bool running();

	virtual vector<GamePlayer*>* players();
	virtual GamePlayer* player(unsigned short int);
	virtual GamePlayer* currentPlayer();
	
	virtual void waitForBegin();
	virtual unsigned int getConnectedPlayers();
	virtual void setConnectedPlayers(unsigned int);
	
	
	
	virtual void refresh(Request*);
	virtual void refresh(string);
	virtual void propage(Move*);
	virtual void handleMove(Move*);
	
	
	virtual unsigned int nextPlayer();
	virtual void endActiveTurn(); 
	
	virtual void promptPause(string = "");
	virtual void clearInputStream();
	virtual bool validInputStream();
	virtual istringstream* promptInput(string = "");


	virtual int winner()=0;
	virtual Move* parseMove(string)=0;
	virtual void makeMove(Move*)=0;
	virtual void runActiveTurn()=0;
	virtual bool endOfGame()=0;
	virtual bool endOfTurn();

	virtual void clear();
	virtual void displayMessage(string message);
	virtual void displayEndOfGame();
	virtual void displayTurn();
	virtual void displayBoard();
	virtual void displayWinner();
	virtual void displayScore();

	virtual void route(Request*);
};
#endif
