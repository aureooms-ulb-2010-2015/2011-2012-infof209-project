#ifndef DEF_APPMAINWINDOW
#define DEF_APPMAINWINDOW

#include <QMainWindow>
#include <QMenuBar>
#include <QAction>
#include <QWidget>
#include <QVBoxLayout>
#include <QStatusBar>
#include <QMessageBox>
#include <string>
#include <QStringList>

#include "GUI_ChangePassword.hpp"
#include "../../GameServerUI.hpp"
#include "../ErrorBox/ErrorBox.hpp"
#include "./HomePage/HomePage.hpp"
#include "./GamePage/GamePage.hpp"
#include "./GamePage/GUI_Bet.hpp"
#include "./PlayingPage/PlayingPage.hpp"
#include "./FriendsPage/FriendsPage.hpp"
#include "./RankingPage/RankingPage.hpp"

using namespace std;

class AppMainWindow : public QMainWindow {
	Q_OBJECT
private:
/* ----- Global ----- */
	string _nickname;
	GameServerUI* _gameServ;
	
	QWidget* _centralWidget;
	QWidget* _globalWidget;
	QVBoxLayout* _globalLayout;

//=== MainWindow ===-=================
/* ----- Menus ----- */
	QMenu* _menuFile;
	QAction* _actionExit;
	QAction* _actionMenu;
	
	QMenu* _menuOptions;
	QAction* _actionPassword;
	
	QMenu* _menuHelp;
	QAction* _actionHelp;
	QAction* _actionAbout;
	
/* ----- Contenu ----- */
	HomePage* _homePage;
	GamePage* _gamePage;
	PlayingPage* _playingPage;
	RankingPage* _rankingPage;
	FriendsPage* _friendsPage;
	
/* ---- StatusBar ----- */
	QStatusBar* _statusBar;
   	

public:
// ===== Constructeur =====
   	AppMainWindow(string Nickname, GameServerUI* GameServ);
   	string getNickname();
   	HomePage* getHomePage();
   	GamePage* getGamePage();
   	PlayingPage* getPlayingPage();
   	RankingPage* getRankingPage();
   	FriendsPage* getFriendsPage();
   	
public slots:
// ==== Global =====
	void s_Exit();
	void s_Menu();
	void s_Password();
	
// ===== Home =====
	void s_H_Games();
	void s_H_Ranking();
	void s_H_Friends();
	
// ===== Game =====
	void s_G_UpdateList();
	void s_G_Join();
	void s_G_PopUpCreate();
	void s_G_Watch();
	void s_G_Home();
	void s_G_NewGame();

// ===== Playing =====
	void s_P_Home();
	void s_P_UpdatePlayersList();

// ===== Ranking =====
	void s_R_Home();
	void s_R_updateRanking();
	
// ===== Friends =====
	void s_F_Add();
	void s_F_Delete();
	void s_F_Home();
	void s_F_Give();
	void s_F_UpdateFriendsList();
};
#endif
