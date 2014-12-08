#include "GUI_CreateGamePopUp.hpp"

using namespace std;

GUI_CreateGamePopUp::GUI_CreateGamePopUp(string name){
	this->setWindowTitle("Nouvelle partie");
	
	this->_cg_layout = new QGridLayout;
	this->_cg_text = new QLabel("Options d'une nouvelle partie :");
	this->_cg_buttonCreate = new QPushButton("Créer");
    this->_cg_typeGame = new QLabel("Type de jeu : ",this);
    this->_cg_nbPlayers = new QLabel("Nombre de joueurs : ",this);
    this->_cg_gameName = new QLabel("Nom de la partie : ",this);    
    
	this->_cg_typeGameBox = new GUI_GameComboBox(this);
	this->_cg_nbPlayersBox = new QComboBox(this);
	this->_cg_nbPlayersBox->addItem("2");
	this->_cg_nbPlayersBox->addItem("3");
	this->_cg_nbPlayersBox->addItem("4");
	this->_cg_nbPlayersBox->setEnabled(false);
	this->_cg_gameNameEdit = new QLineEdit(QString(("Partie de "+name).c_str()), this);

	this->_cg_layout->addWidget(_cg_text, 0, 0, 1, 2);
	this->_cg_layout->addWidget(_cg_typeGame, 1, 0);
	this->_cg_layout->addWidget(_cg_typeGameBox, 1, 1);
	this->_cg_layout->addWidget(_cg_nbPlayers, 2, 0);
	this->_cg_layout->addWidget(_cg_nbPlayersBox, 2, 1);
	this->_cg_layout->addWidget(_cg_gameName, 3, 0);
	this->_cg_layout->addWidget(_cg_gameNameEdit, 3, 1);	
	this->_cg_layout->addWidget(_cg_buttonCreate, 4, 0, 1, 2);
	this->setLayout(_cg_layout);
	
	this->show();

	connect(this->_cg_typeGameBox, SIGNAL(activated(QString)), this, SLOT(s_ModifyNbPlayers(QString)));
}

//=== Getters ==========================================================
QPushButton* GUI_CreateGamePopUp::getCg_buttonCreate(){
	return _cg_buttonCreate;
}
GUI_GameComboBox* GUI_CreateGamePopUp::getCg_typeGameBox(){
	return _cg_typeGameBox;
}
QComboBox* GUI_CreateGamePopUp::getCg_nbPlayersBox(){
	return _cg_nbPlayersBox;
}
QLineEdit* GUI_CreateGamePopUp::getCg_gameNameEdit(){
	return _cg_gameNameEdit;
}

//=== Slots ============================================================
void GUI_CreateGamePopUp::s_ModifyNbPlayers(QString index){
	if(index == "Ludo"){
		this->_cg_nbPlayersBox->setEnabled(true);
	}
	else{
		this->_cg_nbPlayersBox->setEnabled(false);		
	}
}
