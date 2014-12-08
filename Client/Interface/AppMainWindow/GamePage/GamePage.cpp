#include "GamePage.hpp"

using namespace std;


GamePage::GamePage(string Nickname, GameServerUI* GameServ, QWidget* GlobalWidget, QVBoxLayout* GlobalLayout) : Page(Nickname, GameServ){
/* -------------------- Global ----------------------*/
	_gameWidget = new QWidget(GlobalWidget);
	_gameLayout = new QGridLayout(_gameWidget);

/* -------------------- Label Liste --------------------- */
	_g_listeLabel = new QLabel("Liste des Parties", _gameWidget);
	_g_listeLabel->setAlignment(Qt::AlignHCenter| Qt::AlignVCenter);

/* -------------------- Bouton Actualiser --------------------- */
	_g_buttonActu = new QPushButton("Actualiser la liste");
		
/* -------------------- Génération liste --------------------- */

	_g_gameList = new GUI_GamesListWidget(_gameWidget, _gameServ->getGameList());
	
/* -------------------- Widget Boutons --------------------- */
	_g_buttonWidget = new QWidget(_gameWidget);
	_g_buttonLayout = new QHBoxLayout(_g_buttonWidget);
	
	_g_buttonJoin = new QPushButton("Rejoindre");
    _g_buttonLayout->addWidget(_g_buttonJoin);
    
	_g_buttonCreate = new QPushButton("Créer");
    _g_buttonLayout->addWidget(_g_buttonCreate);
    
	_g_buttonWatch = new QPushButton("Regarder");
    _g_buttonLayout->addWidget(_g_buttonWatch);
 
	_g_buttonHome = new QPushButton("Accueil");
    _g_buttonLayout->addWidget(_g_buttonHome);
    
/* -------------------- Widget play --------------------- */
	_gameLayout->addWidget(_g_listeLabel, 0, 0, 1, 1);
	_gameLayout->addWidget(_g_buttonActu, 0, 4, 1, 1);
	_gameLayout->addWidget(_g_gameList, 1, 0, 1, 5);
	_gameLayout->addWidget(_g_buttonWidget, 2, 0, 1, 5);
	
	_gameWidget->setLayout(_gameLayout);
	
/* -------------------- CentralWidget -------------------- */
	GlobalLayout->addWidget(_gameWidget);

/* -------------------- PopUp ------------------------ */
	_g_createGamePopUp = new GUI_CreateGamePopUp(_nickname);
	_g_createGamePopUp->setVisible(false);
	
}

//=== Methodes =========================================================
void GamePage::updateGameList(){
	this->_g_gameList->updateGL(_gameServ->getGameList());
}

//=== Getters ==========================================================
QWidget* GamePage::getGameWidget(){
	return _gameWidget;
}
GUI_GamesListWidget* GamePage::getG_gameList(){
	return _g_gameList;
}
QPushButton* GamePage::getG_buttonActu(){
	return _g_buttonActu;
}
QPushButton* GamePage::getG_buttonJoin(){
	return _g_buttonJoin;
}
QPushButton* GamePage::getG_buttonCreate(){
	return _g_buttonCreate;
}
QPushButton* GamePage::getG_buttonWatch(){
	return _g_buttonWatch;
}
QPushButton* GamePage::getG_buttonHome(){
	return _g_buttonHome;
}
GUI_CreateGamePopUp* GamePage::getG_createGamePopUp(){
	return _g_createGamePopUp;
}
//=== Setters ==========================================================
void GamePage::setGameWidgetVisible(bool visible){
	_gameWidget->setVisible(visible);
}
void GamePage::setCreateGamePopUpVisible(bool visible){
	_g_createGamePopUp->setVisible(visible);
}

//=== Slots ============================================================
