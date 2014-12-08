#ifndef SERVER
#define SERVER

#include "../Common/GenericServer.hpp"
#include "../Library/all.hpp"
#include <string>

using namespace std;

class Server : public GenericServer{
	private :
		struct sockaddr_in _clientAddress;
	public :
		Server(int);
		virtual void init();
		virtual void start();
	protected :
		virtual void initClientSocket();
		virtual struct sockaddr_in * getClientAddress(){ return &_clientAddress;}
};

#endif
