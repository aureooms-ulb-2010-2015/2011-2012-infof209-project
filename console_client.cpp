#include "./Client/Server.hpp"
#include "./Client/ListenerServer.hpp"
#include "./Client/Menu.hpp"
#include "./Client/GameServer.hpp"
#include "Common/Request.hpp"
#include <string>
#include <vector>

#define PORT 3017
using namespace std;


int main(int argc, char* argv[]){
	const char * ip;
	if(argc == 2){
		ip = argv[1];
	}
	else{
    	ip = "127.0.0.1";
    }
	string message, buffer,name;
	int nPlayers;

    Menu * menuCon = new Menu("Menu de connexion");
    menuCon->addField("Vous connecter.");
    menuCon->addField("Vous inscrire.");
    menuCon->set("nick","Votre pseudonyme",0);
    menuCon->set("pass","Votre mot de passe", 0);
    
    Menu * mainMenu = new Menu("Menu principal");
    mainMenu->addField("Vous déconnecter.");
    mainMenu->addField("Ajouter un ami.");
    mainMenu->addField("Supprimer un ami.");
    mainMenu->addField("Voir vos amis.");
    mainMenu->addField("Voir le ranking global.");
    mainMenu->addField("Entrer dans le menu des jeux.");
    mainMenu->addField("Changer de mot de passe");
    mainMenu->set("friend_remove","Pseudonyme de l'ami que vous souhaitez supprimer",3);
    mainMenu->set("friend_add","Pseudonyme de l'ami que vous souhaitez ajouter",2);
    mainMenu->set("new_pass","Nouveau mot de passe",7);
    
    Menu * createGame = new Menu("Créer une partie");
    createGame->addField("Ludo");
    createGame->addField("BackGammon");
    createGame->addField("Dames");
    createGame->addField("Reversi");
    createGame->set("name","Nom de la partie",0);
    createGame->set("nPlayers","Nombre de joueurs",1);
    
    Menu * gameTuto = new Menu("Menu des tutoriels");
    gameTuto->addField("Ludo");
    gameTuto->addField("BackGammon");
    gameTuto->addField("Dames");
    gameTuto->addField("Reversi");
    
    Menu * gameMenu = new Menu("Menu de jeux.");
    gameMenu->addField("Créer une partie.");
    gameMenu->addField("Afficher les parties en cours.");
    gameMenu->addField("Rejoindre une partie.");
    gameMenu->addField("Visioner une partie.");
    gameMenu->addField("Entrer dans le menu des tutoriels.");
    gameMenu->addField("Quitter le menu de jeux.");
    gameMenu->set("gameId","L'identifiant du jeux que vous souhaitez rejoindre",3);
    gameMenu->set("vGameId","L'identifiant du jeux que vous souhaitez rejoindre",4);
    gameMenu->addSubMenu(createGame, 1);
    gameMenu->addSubMenu(gameTuto, 5);
    
    
	
	GameServer * gs = new GameServer(PORT,ip);
    ListenerServer * listener = new ListenerServer(PORT, ip);

	Request * request = new Request(gs);
	while(true){
		if(gs->isLogged()){
		    mainMenu->ask();
			message=mainMenu->getAnswer();
			if(message=="1"){
				gs->logout();
			}
			else if(message=="2"){
				request->makeRequest("ADD","friend");
				request->addAttribute(mainMenu->get("friend_add"));
				request->flush();
			}
			else if(message=="3"){
			     request->makeRequest("REMOVE","friend");
			     request->addAttribute(mainMenu->get("friend_remove"));
			     request->flush();
			}
			else if(message=="4"){
			    gs->displayFriendList();
				getline(cin,buffer);
			}
			else if(message=="5"){
			    gs->displayRanking();
				getline(cin,buffer);
			}
			else if(message=="7"){
			    request->makeRequest("SET","newPassword");
			    request->addAttribute(mainMenu->get("new_pass"));
			    request->flush();
			}
			else if(message=="6"){
			    request->set("name",gs->getName());
			    while(true){
			        gameMenu->ask();
			        message = gameMenu->getAnswer();
			        if(message == "1"){
			            message = gameMenu->getAnswer(1);
			            if(message=="1"){
		                    name="Ludo";
		                    nPlayers=atoi(gameMenu->get("nPlayers").c_str());
	                    }
	                    else if(message=="2"){
		                    name="Backgammon";
		                    nPlayers=2;
	                    }
	                    else if(message=="3"){
		                    name="Dames";
		                    nPlayers=2;
	                    }
	                    else if(message=="4"){
		                    name="Reversi";
		                    nPlayers=2;
	                    }
	                    else{
	                        continue;
	                    }
			            gs->createGame(name,nPlayers,gameMenu->get("name"));
			        }
			        else if(message == "2"){
			            gs->displayGameList();
			        }
			        else if(message == "3"){
			            GameInfos * gameInfos = gs->getGameInfos(atoi(gameMenu->get("gameId").c_str()));
			            request->makeRequest("JOIN","player");
                        request->addAttribute(gameMenu->get("gameId"));
			            if(gameInfos){
		                    gs->startGame(gameInfos->getType(), gameInfos->getRequiredPlayers(),request);
		                }
			        }
			        else if(message=="4"){
			            GameInfos * gameInfos = gs->getGameInfos(atoi(gameMenu->get("vGameId").c_str()));
			            request->makeRequest("JOIN","viewer");
		                request->addAttribute(gameMenu->get("vGameId"));
			            if(gameInfos){
			                gs->viewGame(gameInfos->getType(), gameInfos->getRequiredPlayers(),request);
			            }
			        }
			        else if(message == "5"){
			            message = gameMenu->getAnswer(1);
			            cout<<"---->"<<message<<endl;
			            if(message=="1"){
			            cout<<"OIJOIJOIJOJ"<<endl;
	                    	system("less Tutoriels_Jeux/LudoTuto.txt");          	
			            cout<<"OIJOIJOIJOJ"<<endl;
	                    }
	                    else if(message=="2"){
	                        system("less Tutoriels_Jeux/BackgammonTuto.txt");
	                    }
	                    else if(message=="3"){
	                        system("less Tutoriels_Jeux/DamesTuto.txt");
	                    }
	                    else if(message=="4"){
		                   system("less Tutoriels_Jeux/ReversiTuto.txt");
	                    }
			        }
			        else if(message=="6"){
		                break;
		            }
			    }
			}
			else if(message == "6"){
			    cout<<request->get("playerPoints")<<endl;
			    getline(cin,buffer);
			}
		}
		else{
			menuCon->ask();
			message = menuCon->getAnswer();
			if(message=="1"){
				gs->login(menuCon->get("nick"),menuCon->get("pass"));
			}
			else if(message=="2"){
				gs->createAccount(menuCon->get("nick"),menuCon->get("pass"));
			}
			if(gs->isLogged()){
			    gs->initDatas(listener, menuCon->get("nick"));
			}
		}
	}
	return 0;
}
