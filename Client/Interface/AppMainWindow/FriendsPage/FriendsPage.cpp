#include "FriendsPage.hpp"

using namespace std;

//=== Méthodes =========================================================
FriendsPage::FriendsPage(string Nickname, GameServerUI* GameServ, QWidget* GlobalWidget, QVBoxLayout* GlobalLayout) : Page(Nickname, GameServ){
/* -------------------- Global ----------------------*/
	_friendsWidget = new QWidget(GlobalWidget);
	_friendsLayout = new QGridLayout(_friendsWidget);

/* -------------------- Label Liste --------------------- */
	_f_friendsLabel = new QLabel("Liste d'amis", _friendsWidget);
	_f_friendsLabel->setAlignment(Qt::AlignHCenter| Qt::AlignVCenter);

/* -------------------- Génération liste --------------------- */

	_f_friendsList = new GUI_FriendsListWidget(_friendsWidget, _gameServ->getFriendList());
	
/* -------------------- Nouvel Ami ---------------------- */
	_f_newFriendLabel = new QLabel("Entrez le nom d'un(e) nouvel(le) ami(e)", _friendsWidget);
	_f_newFriendLabel->setAlignment(Qt::AlignHCenter| Qt::AlignVCenter);
	_f_newFriendEdit = new QLineEdit();
	_f_displayMessage = new QLabel("", _friendsWidget);
	_f_displayMessage->setAlignment(Qt::AlignHCenter);
	_f_displayMessage->hide();
	
/* -------------------- Widget Boutons --------------------- */
	_f_buttonWidget = new QWidget(_friendsWidget);
	_f_buttonLayout = new QVBoxLayout(_f_buttonWidget);
	
	_f_buttonAdd = new QPushButton("Ajouter");
    _f_buttonLayout->addWidget(_f_buttonAdd);
    
	_f_buttonDelete = new QPushButton("Supprimer");
    _f_buttonLayout->addWidget(_f_buttonDelete);
    
/* --------------------- Widget Don --------------------- */
    _f_giveWidget = new QWidget(_friendsWidget);
	_f_giveLayout = new QGridLayout(_f_giveWidget);
   	
   	_f_giveLabel = new QLabel("Combien voulez vous donner ?");
   	_f_giveEdit = new QLineEdit("50", _f_giveWidget);
    _f_buttonGive = new QPushButton("                    Faire un don                    ");
    
    _f_giveLayout->addWidget(_f_giveLabel, 0, 0, 1, 5);
    _f_giveLayout->addWidget(_f_giveEdit, 1, 0, 1, 1);
	_f_giveLayout->addWidget(_f_buttonGive, 1, 1, 1, 4);
	
	_f_giveWidget->setLayout(_f_giveLayout);
	
	_f_giveValidator = new QIntValidator(1, 1000000000, _f_giveEdit);
    
/* -------------------- Bouton Home --------------------- */
    _f_buttonHome = new QPushButton("Accueil");
    	
/* -------------------- Widget Home --------------------- */
	_friendsLayout->addWidget(_f_friendsLabel, 0, 0, 1, 4);
	_friendsLayout->addWidget(_f_friendsList, 1, 0, 10, 2);
	_friendsLayout->addWidget(_f_newFriendLabel, 1, 3, 1, 1);
	_friendsLayout->addWidget(_f_newFriendEdit, 2, 3, 1, 1);
	_friendsLayout->addWidget(_f_buttonWidget, 3, 3, 2, 1);
	_friendsLayout->addWidget(_f_displayMessage, 5, 3, 1, 1);
	_friendsLayout->addWidget(_f_giveWidget, 6, 3, 1, 1);
	_friendsLayout->addWidget(_f_buttonHome, 9, 3, 1, 1);
	
	_friendsWidget->setLayout(_friendsLayout);
	
/* -------------------- CentralWidget -------------------- */
	GlobalLayout->addWidget(_friendsWidget);
}

//=== Getters ==========================================================
QWidget* FriendsPage::getFriendsWidget(){
	return _friendsWidget;
}
GUI_FriendsListWidget* FriendsPage::getF_friendsList(){
	return _f_friendsList;
}
QLineEdit* FriendsPage::getF_newFriendEdit(){
	return _f_newFriendEdit;
}	
QPushButton* FriendsPage::getF_buttonAdd(){
	return _f_buttonAdd;
}
QPushButton* FriendsPage::getF_buttonDelete(){
	return _f_buttonDelete;
}
QPushButton* FriendsPage::getF_buttonHome(){
	return _f_buttonHome;
}
QLineEdit* FriendsPage::getF_giveEdit(){
	return _f_giveEdit;
}
QIntValidator* FriendsPage::getF_giveValidator(){
	return _f_giveValidator;
}
QPushButton* FriendsPage::getF_buttonGive(){
	return _f_buttonGive;
}
//=== Setters ==========================================================
void FriendsPage::setFriendsWidgetVisible(bool visible){
	_friendsWidget->setVisible(visible);
}
void FriendsPage::setF_DisplayMessage(string message){
	_f_displayMessage->setText(QString((message.c_str())));
	_f_displayMessage->setVisible(true);	
}
void FriendsPage::initF_newFriendEdit(){
	_f_newFriendEdit->setText("");
}

//=== Slots ============================================================
