#ifndef GENERIC_SERVER
#define GENERIC_SERVER

#include<vector>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include<fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "GenericCommunicator.hpp"
#include "../Library/all.hpp"

class GenericServer : public GenericCommunicator{
	private :
		int _port;
		struct sockaddr_in _serverAddress;
	protected :
		virtual int getPort();
		virtual void setPort(int);
		virtual struct sockaddr_in * getServerAddress();
};

#endif
