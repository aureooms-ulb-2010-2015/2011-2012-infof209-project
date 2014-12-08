#include "GameServerUI.hpp"
#include "./Interface/AppMainWindow/AppMainWindow.hpp"

using namespace std;

GameServerUI::GameServerUI(int port, const char * ip) : GameServer(port, ip){
	this->_interface = NULL;
}

//=== Méthodes GAME =================================================
void GameServerUI::joinGame(string ID){
	Request * request= new Request(this);
	request->makeRequest("JOIN","player");
	request->addAttribute(ID);
	request->flush();
}

void GameServerUI::addGameToList(Request * request){
	GameServer::addGameToList(request);
	if (this->_interface){
		this->_interface->getGamePage()->getG_gameList()->updateGL(this->getGameList());
	}
}

void GameServerUI::removeGameFromList(Request * request){
	GameServer::removeGameFromList(request);
	if (this->_interface){
		this->_interface->getGamePage()->getG_gameList()->updateGL(this->getGameList());
	}
}

void GameServerUI::refreshGameInfos(Request * request){
	GameServer::refreshGameInfos(request);
	if (this->_interface){
		this->_interface->getGamePage()->getG_gameList()->updateGL(this->getGameList());
	}
}

void GameServerUI::addPlayerToRanking(Request * request){
	GameServer::addPlayerToRanking(request);
	if (this->_interface){
		emit si_updateRanking();
	}
}

void GameServerUI::addFriendToList(Request * request){
	GameServer::addFriendToList(request);
	if (this->_interface){
		emit si_updateFriends();
	}
}

void GameServerUI::removeFriendFromList(Request * request){
	GameServer::removeFriendFromList(request);
	if (this->_interface){
		emit si_updateFriends();
	}
}

void GameServerUI::givePoints(string name, int points){
	Request * request= new Request(this);
	request->makeRequest("GIVE", "points");
	request->addAttribute(name);
	request->addAttribute(points);
	request->flush();
}
void GameServerUI::viewGame(string ID){
	Request * request= new Request(this);
	request->makeRequest("JOIN","viewer");
	request->addAttribute(ID);
	request->flush();
}

void GameServerUI::createGame(string type, int number, string name){
    ostringstream stream;
    stream<<number;
    Request * request= new Request(this);
	request->makeRequest("CREATE_GAME",type);
	request->addAttribute(stream.str());
	request->makeRequest("SET","gameName");
	request->addAttribute(name);
	request->flush();
}

void GameServerUI::quit(){
	Request* request = new Request(this);
	request->makeRequest("SET", "quitGame");
	request->flush();
}
//=== Méthodes FRIENDS =================================================
void GameServerUI::getFriends(){
    Request * request= new Request(this);
	request->makeRequest("GET","friends");
	request->flush();
}

void GameServerUI::addFriend(string name){
	Request * request= new Request(this);
	request->makeRequest("ADD","friend");
	request->addAttribute(name);
	request->flush();
}

void GameServerUI::removeFriend(string name){
	Request * request= new Request(this);
	request->makeRequest("REMOVE","friend");
	request->addAttribute(name);
	request->flush();
}

void GameServerUI::displayMessage(Request* request){
	if (request->getName() == "friends"){
		_interface->getFriendsPage()->setF_DisplayMessage(request->getAttributes()[1]);
	}
}

//=== Méthodes RANKING =================================================
void GameServerUI::getPlayerPoints(string name){
	Request * request= new Request(this);
	request->makeRequest("GET", "playerPoints");
	request->addAttribute(name);
	request->flush();
}

//=== Methodes diverses ================================================
void GameServerUI::startChat(Request * request){
	_interface->getPlayingPage()->setChat(request->getAttributes()[1]);
}

void GameServerUI::changePass(string newPass){
	Request * request= new Request(this);
	request->makeRequest("SET", "newPassword");
	request->addAttribute(newPass);
	request->flush();
}

