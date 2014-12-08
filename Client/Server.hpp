#ifndef SERVER
#define SERVER

#include "../Common/GenericServer.hpp"
#include "../Library/all.hpp"

using namespace std;

class Player;
class ListenerServer;

class Server : public GenericServer{
	private :
		Player * _player;
		const char* _ip;
		bool _logged;
		string _name;
	public :
		Server(int port,const char *);
		virtual void init();
		
		virtual void initDatas(ListenerServer *, string){};
		
		virtual void login(string, string);
		virtual void logout();
		virtual void createAccount(string, string);
		virtual Player * getPlayer();
		virtual void setPlayer(Player *);
		virtual bool isLogged();
		virtual string getName();
		virtual void setName(string);
		
		virtual void sendName(string);
		virtual const char * getIp();
		
	protected :
		virtual void initClientSocket();
		virtual void setIp(const char *);

};

#endif
