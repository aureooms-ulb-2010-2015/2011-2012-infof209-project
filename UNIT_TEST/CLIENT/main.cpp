#include "../../Client/Server.hpp"
#include "../../Client/GameServer.hpp"
#include "../../Common/Request.hpp"
#include <string>

#define PORT 3017

using namespace std;

int main(){
	const char * ip = "127.0.0.1";
	string message;
	string buffer;
	GameServer * gs = new GameServer(PORT,ip);
	Request * request = new Request(gs);
	while(true){
	    gs->login();
		ostringstream oss;
		oss<<"1";

		oss.str("");
		oss<<"1";

		if(gs->isLogged()){
			cout<<"Que voulez vous faire ?\n\t1. vous déconnecter.\n\t2. ajouter un ami.\n\t3. supprimer un ami.\n\t4. voir vos amis.\n\t5. entrer dans le menu jeux.\n\t6. Voir mes points."<<endl;
			getline(cin,message);
			if(message=="1"){
				gs->logout();
			}
			else if(message=="2"){
				cout<<"Entrez le pseudo de l'ami que vous voulez ajouter : ";
				getline(cin,buffer);
				request->makeRequest("ADD","friend");
				request->addAttribute(buffer);
				request->flush();
				gs->recvMessage(message);
				cout<<message<<endl;
				sleep(2);
			}
			else if(message=="3"){
			     cout<<"Entrez le pseudo de l'ami que vous voulez supprimer : ";
			     getline(cin, buffer);
			     request->makeRequest("REMOVE","friend");
			     request->addAttribute(buffer);
			     request->flush();
			}
			else if(message=="4"){
			    message = request->get("friends");
				cout<<message<<endl;
				getline(cin,buffer);
			}
			else if(message=="5"){
			    request->set("name",gs->getName());
				gs->menu();
			}
			else if(message == "6"){
			    cout<<request->get("playerPoints")<<endl;
			}
		}
		else{
			cout<<"Que voulez vous faire ?\n\t1. vous connecter.\n\t2. vous inscrire\n";
			getline(cin,message);
			if(message=="1"){
				gs->login();
			}
			else if(message=="2"){
				gs->createAccount();
			}
		}
		/*cout<<"Tapez votre message : "<<endl;
		getline(cin,message);
		cout<<"Message recu : "<<message<<endl;
		s->sendMessage(message);*/
	}
	return 0;
}
