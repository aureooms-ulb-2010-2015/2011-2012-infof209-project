#ifndef BET_CLASS
#define BET_CLASS

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <limits>
#include <utility>

#include "../GameServer.hpp"

class Request;

using namespace std;

class Bet{

protected:
	vector< pair<string,string> >* listOfBets;
	GameServer* _gameServer;

public:
	Bet(GameServer*);
	virtual ~Bet();
    
    virtual void route(Request *);
	virtual void displayWait();
	virtual void displayValid();
	virtual void displayNotValid();
	virtual void displayBets();

	virtual void askAmount();
	virtual void askValidation();

	virtual void addBetToList(Request*);

	virtual GameServer* getGameServer();
	virtual vector< pair<string, string> >* getListOfBets();

	virtual void promptPause(string = "");
	virtual void clearInputStream();
	virtual bool validInputStream();
	virtual istringstream* promptInput(string = "");

};

#endif
