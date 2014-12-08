#include "AppMainWindow.hpp"	

#include <iostream>

using namespace std;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/* * * * * * * * * * * * * * * CONSTRUCTEUR* * * * * * * * * * * * * * */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

AppMainWindow::AppMainWindow(string Nickname, GameServerUI* GameServ){
/* -------------------- Init -------------------- */
	_nickname = Nickname;
	_gameServ = GameServ;
	
	// Icone
	this->setWindowIcon(QIcon("Interface/Images/Vapeur_icon.png"));
	
	// Titre
	string Title = "Vapeur 2.0 - ";
	Title += _nickname;
	this->setWindowTitle(QString(Title.c_str()));;

	// Taille
	this->resize(1024, 724);

	// Background

	// Widget Principal
	_centralWidget = centralWidget();
	_globalWidget = new QWidget(_centralWidget);
	_globalLayout = new QVBoxLayout(_globalWidget);
	
	// Widget Pages
    _homePage = new HomePage(_nickname, _gameServ, _globalWidget, _globalLayout);
    _globalLayout->addWidget(_homePage->getHomeWidget());
	_homePage->setHomeWidgetVisible(true);
	_gamePage = new GamePage(_nickname, _gameServ, _globalWidget, _globalLayout);
    _globalLayout->addWidget(_gamePage->getGameWidget());
	_gamePage->setGameWidgetVisible(false);
	_playingPage = new PlayingPage(_nickname, _gameServ, _globalWidget, _globalLayout);
    _globalLayout->addWidget(_playingPage->getPlayingWidget());
	_playingPage->setPlayingWidgetVisible(false);
	_friendsPage = new FriendsPage(_nickname, _gameServ, _globalWidget, _globalLayout);
    _globalLayout->addWidget(_friendsPage->getFriendsWidget());
	_friendsPage->setFriendsWidgetVisible(false);
	_rankingPage = new RankingPage(_nickname, _gameServ, _globalWidget, _globalLayout);
    _globalLayout->addWidget(_rankingPage->getRankingWidget());
	_rankingPage->setRankingWidgetVisible(false);
	this->setCentralWidget(_globalWidget);
	
/* --------------------- Barres --------------------- */ 
	// Barre Menu File       
	_menuFile = menuBar()->addMenu("Fichier");
	_actionMenu = new QAction("Menu", this);
    _menuFile->addAction(_actionMenu);
	connect(_actionMenu, SIGNAL(triggered()), this, SLOT(s_Menu()));
	_actionExit = new QAction("Quitter", this);
    _menuFile->addAction(_actionExit);
	connect(_actionExit, SIGNAL(triggered()), this, SLOT(s_Exit()));
	
	// Barre Menu Options
	_menuOptions = menuBar()->addMenu("Options");
	_actionPassword = new QAction("Changer mot de passe", this);
	_menuOptions->addAction(_actionPassword);
	connect(_actionPassword, SIGNAL(triggered()), this, SLOT(s_Password()));	
	
	// Barre Menu Help
	_menuHelp = menuBar()->addMenu("Aide");	
    _actionHelp = new QAction("Aide", this);
    _menuHelp->addAction(_actionHelp);
    _actionAbout = new QAction("À Propos", this);
    _menuHelp->addAction(_actionAbout);
    
    // Barre de statut
	_statusBar = statusBar();
	
/* --------------------- Connect --------------------- */
	/* ----- HomePage ------ */
	connect(this->_homePage->getH_buttonGames(), SIGNAL(clicked()), this, SLOT(s_H_Games()));
    connect(this->_homePage->getH_buttonRanking(), SIGNAL(clicked()), this, SLOT(s_H_Ranking()));
    connect(this->_homePage->getH_buttonFriends(), SIGNAL(clicked()), this, SLOT(s_H_Friends()));
	connect(this->_homePage->getH_buttonQuit(), SIGNAL(clicked()), this, SLOT(s_Exit()));
	
	/* ----- GamePage ------ */
	connect(this->_gamePage->getG_buttonActu(), SIGNAL(clicked()), this, SLOT(s_G_UpdateList()));
	connect(this->_gamePage->getG_buttonJoin(), SIGNAL(clicked()), this, SLOT(s_G_Join()));
    connect(this->_gamePage->getG_buttonCreate(), SIGNAL(clicked()), this, SLOT(s_G_PopUpCreate()));
	connect(this->_gamePage->getG_buttonWatch(), SIGNAL(clicked()), this, SLOT(s_G_Watch()));
    connect(this->_gamePage->getG_buttonHome(), SIGNAL(clicked()), this, SLOT(s_G_Home()));
	connect(this->_gamePage->getG_createGamePopUp()->getCg_buttonCreate(), SIGNAL(clicked()), this, SLOT(s_G_NewGame()));

    /* ----- PlayingPage ----- */
	connect(this->_playingPage->getP_buttonHome(), SIGNAL(clicked()), this, SLOT(s_P_Home()));

    /* ----- FriendsPage ----- */
    connect(this->_friendsPage->getF_buttonAdd(), SIGNAL(clicked()), this, SLOT(s_F_Add()));
    connect(this->_friendsPage->getF_buttonDelete(), SIGNAL(clicked()), this, SLOT(s_F_Delete()));
    connect(this->_friendsPage->getF_buttonGive(), SIGNAL(clicked()), this, SLOT(s_F_Give()));
    connect(this->_friendsPage->getF_buttonHome(), SIGNAL(clicked()), this, SLOT(s_F_Home()));
    connect(this->_gameServ, SIGNAL(si_updateFriends()), this, SLOT(s_F_UpdateFriendsList()));
    
	/* ----- RankingPage ----- */
	connect(this->_rankingPage->getR_buttonHome(), SIGNAL(clicked()), this, SLOT(s_R_Home()));
    connect(this->_gameServ, SIGNAL(si_updateRanking()), this, SLOT(s_R_updateRanking()));	
	
	GameServ->setInterface(this);
}
 
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/* * * * * * * * * * * * * * * * GETTERS * * * * * * * * * * * * * * * */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
string AppMainWindow::getNickname(){
	return _nickname;
}
HomePage* AppMainWindow::getHomePage(){
	return _homePage;
}
GamePage* AppMainWindow::getGamePage(){
	return _gamePage;
}
PlayingPage* AppMainWindow::getPlayingPage(){
	return _playingPage;
}
RankingPage* AppMainWindow::getRankingPage(){
	return _rankingPage;
}
FriendsPage* AppMainWindow::getFriendsPage(){
	return _friendsPage;
}
 
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/* * * * * * * * * * * * * * * * SLOTS * * * * * * * * * * * * * * * * */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
//=== Fenêtre Global ===================================================
void AppMainWindow::s_Exit(){
	_gameServ->logout();
	qApp->quit();
}
void AppMainWindow::s_Menu(){
	_gamePage->setGameWidgetVisible(false);
	_rankingPage->setRankingWidgetVisible(false);
	_friendsPage->setFriendsWidgetVisible(false);
	_playingPage->setPlayingWidgetVisible(false);
	if (_playingPage->getGame() != NULL){
		_playingPage->leaveGame();
		_gameServ->quit();
	}
	_homePage->setHomeWidgetVisible(true);
}
void AppMainWindow::s_Password(){
	new GUI_ChangePassword(_gameServ);
}

//=== Fenetre Home =====================================================
void AppMainWindow::s_H_Games(){
	_homePage->setHomeWidgetVisible(false);
	_gamePage->getG_gameList()->updateGL(_gameServ->getGameList());
	_gamePage->setGameWidgetVisible(true);
}
void AppMainWindow::s_H_Ranking(){
	_homePage->setHomeWidgetVisible(false);
	_rankingPage->updateRankings();
	_rankingPage->setRankingWidgetVisible(true);
}
void AppMainWindow::s_H_Friends(){
	_homePage->setHomeWidgetVisible(false);
	_friendsPage->getF_friendsList()->updateF(_gameServ->getFriendList());
	_friendsPage->setFriendsWidgetVisible(true);
}

//=== Fenetre Game =====================================================
void AppMainWindow::s_G_UpdateList(){
	_gamePage->getG_gameList()->updateGL(_gameServ->getGameList());
}
void AppMainWindow::s_G_Join(){
	if (this->_gamePage->getG_gameList()->currentItem() == NULL){
	new ErrorBox("Pas de partie choisie!", "Vous devez sélectionner une partie avant de cliquer sur rejoindre");
	}
	else{
		QString idInput = this->_gamePage->getG_gameList()->currentItem()->text();
		QStringList gameAttr = (idInput).split('\t');
		string ID = gameAttr[0].toStdString();
		GUI_Bet* bet = new GUI_Bet(this->_gameServ);
		this->_gameServ->setBet(bet);
		connect(bet, SIGNAL(si_mustUpdate()), _playingPage, SLOT(s_updatePL()));
		_playingPage->newGame(_gameServ->getGameInfos(atoi(ID.c_str()))->getType(), _gameServ->getGameInfos(atoi(ID.c_str()))->getRequiredPlayers());
		_gameServ->joinGame(ID);
		_gamePage->setGameWidgetVisible(false);	
		_playingPage->setPlayingWidgetVisible(true);

	}
}
void AppMainWindow::s_G_PopUpCreate(){
	_gamePage->setCreateGamePopUpVisible(true);
}
void AppMainWindow::s_G_Watch(){
	if (this->_gamePage->getG_gameList()->currentItem() == NULL){
		new ErrorBox("Pas de partie choisie!", "Vous devez selectionner une partie avant de cliquer sur regarder");
	}
	else{
		QString idInput = this->_gamePage->getG_gameList()->currentItem()->text();
		QStringList gameAttr = (idInput).split('\t');
		string ID = gameAttr[0].toStdString();
		_playingPage->newGame(_gameServ->getGameInfos(atoi(ID.c_str()))->getType(), _gameServ->getGameInfos(atoi(ID.c_str()))->getNumberOfPlayers());
		_gameServ->viewGame(ID);
		_gamePage->setGameWidgetVisible(false);	
		_playingPage->setPlayingWidgetVisible(true);
	}
}
void AppMainWindow::s_G_Home(){
	_gamePage->setGameWidgetVisible(false);
	_homePage->setHomeWidgetVisible(true);
}
void AppMainWindow::s_G_NewGame(){
	QString typeGameInput = this->_gamePage->getG_createGamePopUp()->getCg_typeGameBox()->currentText();
    string typeGameString = typeGameInput.toUtf8().constData();
    
    int nbPlayersString;
    if (typeGameString == "Ludo"){
		QString nbPlayersInput = this->_gamePage->getG_createGamePopUp()->getCg_nbPlayersBox()->currentText();
		nbPlayersString = atoi(nbPlayersInput.toUtf8().constData());
	}
	else{
		nbPlayersString	= 2;
	}
	QString gameNameInput = this->_gamePage->getG_createGamePopUp()->getCg_gameNameEdit()->text();
    string gameNameString = gameNameInput.toUtf8().constData();
    
	GUI_Bet* bet = new GUI_Bet(this->_gameServ);
	this->_gameServ->setBet(bet);
	connect(bet, SIGNAL(si_mustUpdate()), _playingPage, SLOT(s_updatePL()));
	
    _playingPage->newGame(typeGameString, nbPlayersString);
    _gameServ->createGame(typeGameString, nbPlayersString, gameNameString);
    this->_gamePage->setCreateGamePopUpVisible(false);
	_gamePage->setGameWidgetVisible(false);	
	_playingPage->setPlayingWidgetVisible(true);
}

//=== Fenetre Playing ==================================================
void AppMainWindow::s_P_Home(){
	_playingPage->setPlayingWidgetVisible(false);
	_playingPage->leaveGame();
	_gameServ->quit();
	_homePage->setHomeWidgetVisible(true);
}
void AppMainWindow::s_P_UpdatePlayersList(){
	_playingPage->getP_playersList()->UpdatePL(_gameServ);
}	
//=== Fenetre Friends ==================================================
void AppMainWindow::s_F_Add(){
	if (this->_friendsPage->getF_newFriendEdit()->text() == NULL){
		new ErrorBox("Aucun nom entré!", "Vous devez entrer le nom d'un(e) ami(e) avant de cliquer sur ajouter.");
	}
	else{
		QString nameInput = this->_friendsPage->getF_newFriendEdit()->text();
		string name = nameInput.toStdString();
		_gameServ->addFriend(name);
		this->_friendsPage->initF_newFriendEdit();
	}
}
void AppMainWindow::s_F_Delete(){
	if (this->_friendsPage->getF_friendsList()->currentItem() == NULL){
		new ErrorBox("Pas d'ami(e) choisi(e)!", "Vous devez selectionner un(e) ami(e) avant de cliquer sur supprimer.");
	}
	else{
		QString nameInput = this->_friendsPage->getF_friendsList()->currentItem()->text();
		QStringList parseName = nameInput.split('\t');
		string name = parseName[0].toStdString();		
		_friendsPage->setF_DisplayMessage("\""+name+"\" à été supprimé de la liste d'amis");
		_gameServ->removeFriend(name);
		_friendsPage->getF_friendsList()->updateF(_gameServ->getFriendList());
	}
}
void AppMainWindow::s_F_Home(){
	_friendsPage->setFriendsWidgetVisible(false);
	_homePage->setHomeWidgetVisible(true);
}
void AppMainWindow::s_F_Give(){	
	QString nbPoints = _friendsPage->getF_giveEdit()->text();
	int pos = 0;
	if (this->_friendsPage->getF_friendsList()->currentItem() == NULL){
		new ErrorBox("Pas d'ami selectionné!", "Vous devez selectionner un ami avant de cliquer sur faire un don.");
	}
	else if(_friendsPage->getF_giveValidator()->validate(nbPoints, pos) == 1){
		new ErrorBox("Valeur entrée incorrecte!", "Vous devez au moins donner 1 point.");
	}
	else if(_friendsPage->getF_giveValidator()->validate(nbPoints, pos) == 0){
		new ErrorBox("Caractères entrés incorrects!", "Vous devez enter un nombre entier superieur a 1.");
	}
	else{
		QString nameInput = this->_friendsPage->getF_friendsList()->currentItem()->text();
		string name = nameInput.toStdString();
		int nbPointsInt = nbPoints.toInt();
		_gameServ->givePoints(name, nbPointsInt);
	}
}

void AppMainWindow::s_F_UpdateFriendsList(){
	this->getFriendsPage()->getF_friendsList()->updateF(_gameServ->getFriendList());
}
//=== Fenetre Ranking ==================================================
void AppMainWindow::s_R_Home(){
	this->_rankingPage->setRankingWidgetVisible(false);
	this->_homePage->setHomeWidgetVisible(true);
}
void AppMainWindow::s_R_updateRanking(){
	this->_rankingPage->updateRankings();
}

