#ifndef LISTENER_SERVER
#define LISTENER_SERVER

#include "GameServer.hpp"

class ListenerServer : public Server, public Thread{
    
    public:
        GameServer * _server;
    public:
        ListenerServer(int,const char *);
        virtual void * run(void *);
        virtual void init(string name);
        virtual GameServer * getServer(){return _server;}
        virtual void setServer(GameServer * server){_server = server;}
};

#endif
