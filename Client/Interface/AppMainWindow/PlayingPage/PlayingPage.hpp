#ifndef DEF_PLAYINGPAGE
#define DEF_PLAYINGPAGE

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <string>

#include "GUI_Bet.hpp"
#include "GUI_UsersListWidget.hpp"
#include "../GameServerUI.hpp"
#include "../Server.hpp"
#include "../Page.hpp"
#include "../../../Chat_GUI/GUI_Chat.h"
#include "../Games/Ludo/Ludowindow/LudoWindow.hpp"
#include "../Games/Checkers/GuiCheckersGame.hpp"
#include "../Games/Reversi/ReversiWindow/GUI_Reversi_Board.h"
#include "../Games/Backgammon/BackgammonUI.hpp"


/*
 * Include des jeux et du chat
 */

class PlayingPage : public Page {
	Q_OBJECT
private:
/* ----- Global ----- */
    QWidget* _playingWidget;
   	QGridLayout *_playingLayout;

/* ----- Liste Users ----- */
	GUI_UsersListWidget* _p_playersList;	

/* ----- Jeu ----- */
	QWidget* _p_game;
	
/* ----- Chat ----- */
	GUI_Chat* _p_chat;

/* ---- Bouton Home ----- */
    QPushButton* _p_buttonHome;
    
public:
	void updatePlayersList();
	void newGame(string typeOfGame, int nbPlayers);
	
/* ----- Getters ----- */
	QWidget* getGame();
	QWidget* getPlayingWidget();
	GUI_UsersListWidget* getP_playersList();
	QPushButton* getP_buttonHome();

/* ----- Setters ----- */
	void setPlayingWidgetVisible(bool visible);
	void setChat(string);
	void leaveGame();

/* ----- Constructeurs ----- */
	PlayingPage(string Nickname, GameServerUI* GameServ, QWidget* GlobalWidget, QVBoxLayout* GlobalLayout);

public slots:
	void s_setChat(QString);
	void s_updatePL();
	
signals:
	void si_setChat(QString);

};
#endif
