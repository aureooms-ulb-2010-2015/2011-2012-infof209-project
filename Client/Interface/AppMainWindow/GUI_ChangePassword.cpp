#include "GUI_ChangePassword.hpp"

GUI_ChangePassword::GUI_ChangePassword(GameServerUI* GameServ){
	this->_gameServ = GameServ;
	
	this->setWindowTitle("Changement de mot de passe");
	
	this->_cp_layout = new QGridLayout;
	this->_cp_text = new QLabel("Changement de mot de passe");
	
	this->_cp_oldPass = new QLabel("Ancien mot de passe", this);
   	this->_cp_oldPassEdit = new QLineEdit(this);
    this->_cp_oldPassEdit->setEchoMode(QLineEdit::Password);
    
   	this->_cp_newPass = new QLabel("Nouveau mot de passe", this);
   	this->_cp_newPassEdit = new QLineEdit(this);
    this->_cp_newPassEdit->setEchoMode(QLineEdit::Password);
    
	this->_cp_buttonConfirm = new QPushButton("Changer");

	this->_cp_layout->addWidget(this->_cp_text, 0, 0, 1, 2);
	this->_cp_layout->addWidget(this->_cp_oldPass, 1, 0);
	this->_cp_layout->addWidget(this->_cp_oldPassEdit, 1, 1);
	this->_cp_layout->addWidget(this->_cp_newPass, 2, 0);
	this->_cp_layout->addWidget(this->_cp_newPassEdit, 2, 1);
	this->_cp_layout->addWidget(this->_cp_buttonConfirm, 3, 0, 1, 2);
	this->setLayout(_cp_layout);
	
	this->show();
	connect(this->_cp_buttonConfirm, SIGNAL(clicked()), this, SLOT(s_ChangePass()));
}
	
QPushButton* GUI_ChangePassword::getCp_buttonConfirm(){
	return _cp_buttonConfirm;
}

QLineEdit* GUI_ChangePassword::getCp_oldPassEdit(){
	return _cp_oldPassEdit;
}

QLineEdit* GUI_ChangePassword::getCp_newPassEdit(){
	return _cp_newPassEdit;
}

void GUI_ChangePassword::s_ChangePass(){
	QString oldPassInput = getCp_oldPassEdit()->text();
    string oldPassString = oldPassInput.toUtf8().constData();
    
	QString newPassInput = getCp_newPassEdit()->text();
    string newPassString = newPassInput.toUtf8().constData();
	
	if(newPassString.size() >= 6){
		this->_gameServ->changePass(newPassString);
		new ErrorBox("Mot de passe changé!", "Votre mot de passe à été changé.");
	}
	else{
		new ErrorBox("Nouveau mot de passe incorrect!", "Veuillez choisir un mot de passe de minimum 6 caractères.");
	}
}	
