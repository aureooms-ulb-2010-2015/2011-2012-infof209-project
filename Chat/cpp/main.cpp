#include "../h/Chat_client.h"

int main(int argc, char* argv[]){
	if(argc == 4){
		Chat_client client(argv[1],argv[2],argv[3]);
		client.start();
		pthread_join(*client.getThread(),NULL);
	}
	else{
		Chat_client client;
		client.start();
		pthread_join(*client.getThread(),NULL);
	}

	return 0;
}
