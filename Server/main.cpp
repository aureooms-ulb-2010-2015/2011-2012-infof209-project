#include "Server.hpp"
#include "ServerGame.hpp"


#include "../Chat/h/Chat_server.h"
#define PORT 3017

int main(){
	system("clear");
	system("mkdir -p cache_Clients");
	system("mkdir -p cache_Games");
	system("mkdir -p cache_Ranking");
	system("touch cache_Clients/database.txt");

	Chat_server* server = new Chat_server();
	server->start();

	ServerGame * sg = new ServerGame(PORT);
	sg->start();

	return 0;
}
