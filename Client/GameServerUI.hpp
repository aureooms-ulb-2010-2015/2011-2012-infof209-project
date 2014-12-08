#ifndef DEF_GAMESERVERUI_H
#define DEF_GAMESERVERUI_H

#include <string>
#include <QObject>

class AppMainWindow;
class GUI_Bet;
#include "GameServer.hpp"


class GameServerUI : public QObject, public GameServer{
	Q_OBJECT
private:
		AppMainWindow* _interface;
		
public:		
		GameServerUI(int ,const char *);
		
		
		virtual void setInterface(AppMainWindow* interface){this->_interface = interface;}
		virtual AppMainWindow* getInterface(){return _interface;}
		
		virtual void createGame(string, int, string);	
		virtual void joinGame(string ID);	
		virtual void viewGame(string ID);
		virtual void quit();
					
		virtual void getFriends();
		virtual void addFriend(string name);
		virtual void removeFriend(string name);
		virtual void givePoints(string, int);

		void displayMessage(Request *);
			
		virtual void getPlayerPoints(string name);
			
		void changePass(string newPass);
	
		virtual void startChat(Request *);
	
		virtual void addGameToList(Request *);
		virtual void removeGameFromList(Request *);
		virtual void refreshGameInfos(Request *);
		
		virtual void addPlayerToRanking(Request *);

		virtual void addFriendToList(Request *);
		virtual void removeFriendFromList(Request *);
		
signals:
		void si_updateRanking();
		void si_updateFriends();
};
#endif
