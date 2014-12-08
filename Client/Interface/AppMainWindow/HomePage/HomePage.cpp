#include "HomePage.hpp"

//=== Methodes =====================================================
HomePage::HomePage(string Nickname, GameServerUI* GameServ, QWidget* GlobalWidget, QVBoxLayout* GlobalLayout) : Page(Nickname, GameServ){
/* -------------------- Global ----------------------*/	
	_homeWidget = new QWidget(GlobalWidget);
	_homeLayout = new QVBoxLayout(_homeWidget);
	
/* -------------------- Label Bienvenue --------------------- */
	_h_welcomeLabel = new QLabel("Bienvenue sur Vapeur 2.0", _homeWidget);
	_h_welcomeLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

/* -------------------- Widget Boutons --------------------- */
	_h_buttonWidget = new QWidget(_homeWidget);
	_h_buttonLayout = new QHBoxLayout(_h_buttonWidget);	
	
	_h_buttonGames = new QPushButton("Jeux");
    _h_buttonLayout->addWidget(_h_buttonGames);
    
    _h_buttonRanking = new QPushButton("Classement");
    _h_buttonLayout->addWidget(_h_buttonRanking);
    
    _h_buttonFriends = new QPushButton("Amis");
    _h_buttonLayout->addWidget(_h_buttonFriends);
    
	_h_buttonQuit = new QPushButton("Quitter");
    _h_buttonLayout->addWidget(_h_buttonQuit);

	_h_buttonWidget->setLayout(_h_buttonLayout);

/* -------------------- Widget Home --------------------- */
	_homeLayout->addWidget(_h_welcomeLabel);
	_homeLayout->addWidget(_h_buttonWidget);
	
	_homeWidget->setLayout(_homeLayout);
/* -------------------- CentralWidget -------------------- */
	GlobalLayout->addWidget(_homeWidget);
}

//=== Getters ==========================================================
QWidget* HomePage::getHomeWidget(){
	return _homeWidget;
}
QPushButton* HomePage::getH_buttonGames(){
	return _h_buttonGames;
}
QPushButton* HomePage::getH_buttonRanking(){
	return _h_buttonRanking;
}
QPushButton* HomePage::getH_buttonFriends(){
	return _h_buttonFriends;
}
QPushButton* HomePage::getH_buttonQuit(){
	return _h_buttonQuit;
}

//=== Setters ==========================================================
void HomePage::setHomeWidgetVisible(bool visible){
	_homeWidget->setVisible(visible);
}

//=== Slots ============================================================
