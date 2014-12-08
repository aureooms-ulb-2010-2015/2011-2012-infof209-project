#ifndef DEF_GAMEPAGE
#define DEF_GAMEPAGE
#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QListWidget>
#include <QWidget>
#include <QHBoxLayout>
#include <string>

#include "../../../GameServerUI.hpp"
#include "../Page.hpp"
#include "GUI_GamesListWidget.hpp"
#include "GUI_CreateGamePopUp.hpp"

class GamePage : public Page{
	Q_OBJECT
private:
/* ----- Global Widget ----- */
    QWidget* _gameWidget;
   	QGridLayout* _gameLayout;

/* ----- Label Jeux----- */
	QLabel* _g_listeLabel;
	
/* ---- Bouton Actu ----- */
	QPushButton* _g_buttonActu;

/* ----- Liste Parties ----- */
	GUI_GamesListWidget* _g_gameList;
	
/* ----- Widget Boutons ----- */		
    QWidget* _g_buttonWidget;
   	QHBoxLayout* _g_buttonLayout;

    QPushButton* _g_buttonJoin;
    QPushButton* _g_buttonCreate;
    QPushButton* _g_buttonWatch;
    QPushButton* _g_buttonHome;

/* ----- Pop up pour créer une partie ----- */
   	GUI_CreateGamePopUp* _g_createGamePopUp;

public:
	void updateGameList();
	void createGamePopUp();
	
/* ----- Getters ----- */
    QWidget* getGameWidget();	
	GUI_GamesListWidget* getG_gameList();
	QPushButton* getG_buttonActu();
    QPushButton* getG_buttonJoin();
    QPushButton* getG_buttonCreate();
    QPushButton* getG_buttonWatch();
    QPushButton* getG_buttonHome();
	GUI_CreateGamePopUp* getG_createGamePopUp();
	
/* ----- Setters ----- */
	void setGameWidgetVisible(bool visible);
	void setCreateGamePopUpVisible(bool visible);
   	
/* ----- Constructeur ----- */
	GamePage(string Nickname, GameServerUI* GameServ, QWidget* GlobalWidget, QVBoxLayout* GlobalLayout);
};
#endif
