#ifndef CLIENT
#define CLIENT

#include<iostream>
#include<string>
#include "../Library/all.hpp"
#include "../Common/GenericCommunicator.hpp"
#include "../Common/Request.hpp"

using namespace std;

class ServerGame;

class Client : public Thread, public GenericCommunicator{
	public :
		static unsigned int id;
		
	private :
		ServerGame * _gameServer;
		GenericCommunicator _notifier;
		string _name;
		string _password;
		unsigned int _id;
		
	public :
	    bool LOGGED;
		static unsigned int getNewId();
		Client(string);
		Client(int);
		Client(string, string);
		Client(string, int);
		
		virtual void route(Request *);
		virtual void display(std::ostream &out);
		virtual bool isPlayer();
		virtual void loadGlobalRanking();
		
		virtual void setNewPassword(string);
		//Getters
		
		virtual string getName(){return _name;}
		virtual string getPassword(){return _password;}
		virtual unsigned int getId() const{return _id;}
		virtual ServerGame * getGameServer(){return _gameServer;}
		virtual GenericCommunicator * getNotifier(){return &_notifier;}
		
		//Setters
		
		virtual void setName(string name){_name = name;}
		virtual void setPassword(string pass){_password = pass;}
		virtual void setGameServer(ServerGame * server){_gameServer=server;}
		virtual void setNotifier(GenericCommunicator i){_notifier = i;}
	
	protected :
	    virtual void * run(void *);
	    //Routing
		virtual void set(string,string);
		virtual void get(Request *);
		virtual void create(string, string);
		virtual void add(string,string);
		virtual void remove(string, string);
	    //Autres
	    virtual bool login();
	    virtual bool exists(string);
		virtual void addAccountToFile(string, string);
		virtual void addFriend(string user, string friendName);
		virtual void removeFriend(string user, string friendName);
		virtual bool checkPassword(string ,string);
		virtual bool existsInFriendlist(string nickname,string friendName);
		virtual void getFriends(Request * request);
		virtual void createGame(string,string){};
		
	private :
		virtual void setNewId();
};

std::ostream &operator<<(std::ostream &out, Client &client);
std::ostream &operator<<(std::ostream &out, Client *client);
#endif
