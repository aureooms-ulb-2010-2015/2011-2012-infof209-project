#ifndef GENERIC_COMMUNICATOR
#define GENERIC_COMMUNICATOR

#include <string>
#include "../Library/all.hpp"

class Request;

using namespace std;

class GenericCommunicator{
	private :
		int _sockFd;
	public :
	    GenericCommunicator(){}
	    GenericCommunicator(int s){
	        _sockFd = s;
	    }
		virtual void sendMessage(string &);
		virtual void recvMessage(string &);
		virtual void sendRequest(Request * );
		virtual Request * recvRequest();
		virtual void recvRequest(Request * );
		virtual void sendInt(int);
		virtual int recvInt();
		virtual int extractInteger(string);
		virtual void setSocket(int);
		virtual int getSocket();
		virtual bool recvBool();
		virtual void sendBool(bool b);
};
#endif
