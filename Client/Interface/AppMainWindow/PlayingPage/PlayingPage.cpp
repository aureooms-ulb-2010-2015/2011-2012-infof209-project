#include "PlayingPage.hpp"
#include <stdio.h>
#include <stdlib.h>

using namespace std;

PlayingPage::PlayingPage(string Nickname, GameServerUI* GameServ, QWidget* GlobalWidget, QVBoxLayout* GlobalLayout) : Page(Nickname, GameServ){
/* -------------------- Global ----------------------*/
	_playingWidget = new QWidget(GlobalWidget);
	_playingLayout = new QGridLayout(_playingWidget);

/* -------------------- Génération liste --------------------- */
	_p_playersList = new GUI_UsersListWidget(_playingWidget);
/* -------------------- Widgets Jeu/chat -------------------- */
	_p_game = NULL;
	_p_chat = NULL;
	
	_p_buttonHome = new QPushButton("Quitter La partie");
	
/* -------------------- Widget play --------------------- */
	_playingLayout->addWidget(_p_playersList, 0, 5, 1, 1, Qt::AlignTop);
									(_p_chat, 1, 5, 3, 1);
	_playingLayout->addWidget(_p_buttonHome, 4, 5, 4, 1);
	
	_playingWidget->setLayout(_playingLayout);
	
/* -------------------- CentralWidget -------------------- */
	GlobalLayout->addWidget(_playingWidget);
	connect(this,SIGNAL(si_setChat(QString)), this, SLOT(s_setChat(QString)));
}

//=== Methodes =========================================================
void PlayingPage::newGame(string typeOfGame, int nbPlayers){
	Game* game;
	if(typeOfGame == "Ludo"){
		LudoWindow* gamex = new LudoWindow(nbPlayers, _gameServ);
		this->_p_game = qobject_cast<QWidget*>(gamex);
		game = gamex;
		
	}
	else if (typeOfGame == "Backgammon"){
		BackgammonUI* gamex = new BackgammonUI(_gameServ);
		this->_p_game = qobject_cast<QWidget*>(gamex);
		game = gamex;
	}
	else if (typeOfGame == "Reversi"){
		GUI_Reversi_Board* gamex =  new GUI_Reversi_Board(_gameServ);
		this->_p_game = qobject_cast<QWidget*>(gamex);
		game = gamex;
	}
	else if (typeOfGame == "Dames"){
		GuiCheckersGame* gamex =  new GuiCheckersGame(_gameServ);
		this->_p_game = qobject_cast<QWidget*>(gamex);
		game = gamex;
	}
	_playingLayout->addWidget(this->_p_game, 0, 0, 5, 5);
	_gameServ->setGame(game);
}
//=== Getters ==========================================================
QWidget* PlayingPage::getGame(){
	return _p_game;
}

QWidget* PlayingPage::getPlayingWidget(){
	return _playingWidget;
}

GUI_UsersListWidget* PlayingPage::getP_playersList(){
	return _p_playersList;
}
QPushButton* PlayingPage::getP_buttonHome(){
	return _p_buttonHome;
}

//=== Setters ==========================================================
void PlayingPage::setPlayingWidgetVisible(bool visible){
	_playingWidget->setVisible(visible);
}
void PlayingPage::setChat(string ID){
	emit si_setChat(QString(ID.c_str()));
}

void PlayingPage::leaveGame(){
	_playingLayout->removeWidget(_p_game);
	delete _p_game;
	if (_p_chat){
		_playingLayout->removeWidget(_p_chat);
		delete _p_chat;
	}
}

// === Slots ==========================================================
void PlayingPage::s_setChat(QString ID){
	_p_chat = new GUI_Chat(_gameServ->getIp(), getNickname(), ID.toStdString());
	_playingLayout->addWidget(_p_chat, 1, 5, 3, 1);
}

void PlayingPage::s_updatePL(){
	this->getP_playersList()->UpdatePL(_gameServ);
}
