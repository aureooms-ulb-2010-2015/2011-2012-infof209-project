#include "RankingPage.hpp"

using namespace std;

RankingPage::RankingPage(string Nickname, GameServerUI* GameServ, QWidget* GlobalWidget, QVBoxLayout* GlobalLayout) : Page(Nickname, GameServ){
/* -------------------- Global ----------------------*/
	_rankingWidget = new QWidget(GlobalWidget);
	_rankingLayout = new QGridLayout(_rankingWidget);
	
/* ------------------- Ranking Tabs -------------------- */
	_rankingTab = new QTabWidget(_rankingWidget);
	_globalRanking = new GUI_RankingWidget(_rankingTab, _gameServ->getRanking());
	_friendsRanking = new GUI_RankingWidget(_rankingTab, _gameServ->getFriendList());
	this->_rankingTab->addTab(_globalRanking, "Classement Global");
	this->_rankingTab->addTab(_friendsRanking, "Classement Amis");

/* -------------------- Bouton Home --------------------- */
    _r_buttonHome = new QPushButton("Accueil");

/* -------------------- Widget Ranking --------------------- */
	_rankingLayout->addWidget(_rankingTab, 0, 0, 10, 10);
	_rankingLayout->addWidget(_r_buttonHome, 10, 5, 1, 1);	
	
	_rankingWidget->setLayout(_rankingLayout);
/* -------------------- CentralWidget -------------------- */
	GlobalLayout->addWidget(_rankingWidget);
}

//=== Méthodes =========================================================
void RankingPage::updateRankings(){
	_globalRanking->updateR(_gameServ->getRanking());
	_friendsRanking->updateR(_gameServ->getFriendList());
}
//=== Getters ==========================================================
QWidget* RankingPage::getRankingWidget(){
	return _rankingWidget;
}
QPushButton* RankingPage::getR_buttonHome(){
	return _r_buttonHome;
}
//=== Setters ==========================================================
void RankingPage::setRankingWidgetVisible(bool visible){
	_rankingWidget->setVisible(visible);
}

