#include "../h/Chat_server.h"

int main(){
	Chat_server* server new Chat_server();
	server->start();
	pthread_join(*server.getThread(),NULL);
	return 0;
}
