#ifndef GAMEINSTANCE
#define GAMEINSTANCE

#include <vector>
#include <string>

class Player;
class ServerGame;

using namespace std;

class GameInstance{
	private :
	    static int id;
		vector<Player *> _players;
		vector<Player *> _viewers;
		ServerGame * _server;
		vector<string> _moves;
		string _type;
		string _name;
		int _turn;
		int _playersRequired;
		bool _busy;
		int _betConfirmed;
		int _betRefused;
		int _totalPoints;
		int _totalBets;
		int _id;
		int _globalId;
		Player * _winner;
	
	public :
		GameInstance(int maxPlayers, ServerGame *);
		GameInstance();
		
		virtual void display(std::ostream &flux);
		virtual void removePlayer(Player * player);
		virtual bool isTurn(int);
		virtual bool isTurn(Player *);
		virtual bool isBusy(){return _busy;}
		virtual bool isFull();
		virtual void addPlayer(Player *);
		virtual void addViewer(Player *);
		virtual void addMove(string);
		virtual void addToTotalPoints(int points){_totalPoints+=points; _totalBets++;}
		
		virtual bool betContract(){return (_betConfirmed == _playersRequired);}
		virtual bool allrespondedToContract(){ return ( (_betConfirmed + _betRefused ) == _playersRequired);}
		virtual bool allHaveBet(){return (_totalBets == _playersRequired);}
		virtual void initBetContract(){_betConfirmed = 0; _betRefused =0;_totalPoints =0; _totalBets =0;}
		virtual void signContract(){_betConfirmed++;}
		virtual void refuseContract(){_betRefused++;}
		virtual void activateBets();
		
		virtual void endOfGame();
		
		virtual void signalNoContract();
		
		//Getters
		virtual string getType(){return _type;}
		virtual string getName(){return _name;}
		virtual string getLastMove();
		virtual Player * getPlayer(int);
		virtual Player * getWinner(){return _winner;}
		virtual ServerGame * getServer(){return _server;}
		virtual vector<Player *> * getPlayers(){return &_players;}
		virtual vector<Player *> * getViewers(){return &_viewers;}
		virtual vector<string> * getMoves(){return &_moves;}
		virtual int getNumberOfPlayers();
		virtual int getNumberOfViewers();
		virtual int getRequiredPlayers(){return _playersRequired;}
		virtual int getTurn(){return _turn;}
		virtual int getId(){return _id;}
		virtual int getGlobalId(){return _globalId;}
		virtual int getTotalPoints(){return _totalPoints;}
		
		//Setters	
		virtual void setWinner(int i){_winner = _players[i];}
		virtual void setNextTurn();
		virtual void setType(string type){_type=type;}
		virtual void setName(string name){_name=name;}
		virtual void setServer(ServerGame * server){_server = server;}
		virtual void setId(int id){_id=id;}
		virtual void setTurn(int turn){_turn = turn;}
		virtual void setIsBusy(bool val){_busy = val;}
		
};

std::ostream &operator<<(std::ostream &out, GameInstance &);
std::ostream &operator<<(std::ostream &out, GameInstance *);

#endif
