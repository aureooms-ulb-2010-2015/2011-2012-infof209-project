#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>

#include "LoginPage.hpp"

#define PORT 3017

using namespace std;

void LoginPage::getIPEdit(){
    QString ipInput = this->_ipEdit->text();
    _ip = ipInput.toStdString();
}
	
LoginPage::LoginPage(GameServerUI* GameServ){
	_gameServ = GameServ;
	_ip = "127.0.0.1";
			
	// Attributs de Window
	this->setWindowIcon(QIcon("./Interface/Images/Vapeur_icon.png"));
    this->setWindowTitle("Page de Login");
    
	// Widget Principal
	_globalLayout = new QGridLayout(this);

	// Widgets (Boutons/Labels/...)
    _buttonValidation = new QPushButton("Valider",this);
    _buttonCreateAccount = new QPushButton("Creer nouveau compte",this);
        
    _nicknameEdit = new QLineEdit(this);
    _passwordEdit = new QLineEdit(this);
    _passwordEdit->setEchoMode(QLineEdit::Password);
    _ipEdit = new QLineEdit("127.0.0.1", this);
    
    _nicknameLabel = new QLabel("Nom d'utilisateur : ",this);
    _passwordLabel = new QLabel("Mot de passe : ",this);
    _ipLabel = new QLabel("Adresse IP du serveur : ", this);
    
    _globalLayout->addWidget(_nicknameLabel, 0, 0);
    _globalLayout->addWidget(_nicknameEdit, 0, 1);
    _globalLayout->addWidget(_passwordLabel, 1, 0);
    _globalLayout->addWidget(_passwordEdit, 1, 1);
    _globalLayout->addWidget(_ipLabel, 4, 0);
    _globalLayout->addWidget(_ipEdit, 4, 1);
    _globalLayout->addWidget(_buttonValidation, 6, 0);
    _globalLayout->addWidget(_buttonCreateAccount, 6, 1);
    
    this->setLayout(_globalLayout);
    
	connect(_buttonValidation, SIGNAL(clicked()), this, SLOT(s_validation()));
    connect(_buttonCreateAccount, SIGNAL(clicked()), this, SLOT(s_createAccount()));
}

LoginPage::~LoginPage(){
}

void LoginPage::s_validation(){
    QString nicknameInput = this->_nicknameEdit->text();
    _nickname = nicknameInput.toStdString();
	
    QString passwordInput = this->_passwordEdit->text();
    _password = passwordInput.toStdString();
    
	getIPEdit();
		
	// Connection au serveur
	_gameServ = new GameServerUI(PORT, _ip.c_str());
	_listenerServ = new ListenerServer(PORT, _ip.c_str());	
	
	_gameServ->login(_nickname, _password);
	if(_gameServ->isLogged()){
		_gameServ->initDatas(_listenerServ, _nickname);
		
		// Mot de passe valide, redirection vers la Homepage
		AppMainWindow* Window = new AppMainWindow(_nickname, _gameServ);
		Window->show();
		this->close();
	}
	else{
		// Mauvais mot de passe
		new ErrorBox("Mauvais Mot de passe!", "Mauvais mot de passe, veuillez réessayer.");
	}
}

void LoginPage::s_createAccount(){
	_createAccountPopUp = new QDialog(this);
	_createAccountPopUp->setWindowTitle("Nouveau Compte");
	
	_ca_layout = new QGridLayout;
	_ca_text = new QLabel("Veuillez entrez un nom d'utilisateur ainsi qu'un mot de passe.");
	_ca_buttonCreate = new QPushButton("Creer");
    _ca_nickname = new QLabel("Nom d'utilisateur : ",this);
    _ca_password = new QLabel("Mot de passe : ",this);
    
	_ca_nicknameEdit = new QLineEdit(this);
	_ca_passwordEdit = new QLineEdit(this);
	_ca_passwordEdit->setEchoMode(QLineEdit::Password);

	_ca_layout->addWidget(_ca_text, 0, 0, 1, 2);
	_ca_layout->addWidget(_ca_nickname, 1, 0);
	_ca_layout->addWidget(_ca_nicknameEdit, 1, 1);
	_ca_layout->addWidget(_ca_password, 2, 0);
	_ca_layout->addWidget(_ca_passwordEdit, 2, 1);
	_ca_layout->addWidget(_ca_buttonCreate, 3, 0, 1, 2);
	_createAccountPopUp->setLayout(_ca_layout);
	
	connect(_ca_buttonCreate, SIGNAL(clicked()), this, SLOT(s_create()));
	_createAccountPopUp->show();
	this->hide();
}

void LoginPage::s_create(){
    QString nicknameInput = this->_ca_nicknameEdit->text();
    _nickname = nicknameInput.toStdString();
	
    QString passwordInput = this->_ca_passwordEdit->text();
    _password = passwordInput.toStdString();
    
	getIPEdit();
	
    if (_nickname.size() < 3){
		// nickname trop court
		new ErrorBox("Nom trop court!","Nom d'utilisateur trop court,\n la taille minimale est de 3 caracteres.");
	}
	else if (_password.size() < 6){
		// password trop court
		new ErrorBox("Mot de passe trop court!", "Votre mot de passe est trop court,\n la taille minimale est de 6 caracteres.");
	}
	else{
		// Connection au serveur
		_gameServ = new GameServerUI(PORT, _ip.c_str());
		_listenerServ = new ListenerServer(PORT, _ip.c_str());
		this->_gameServ->createAccount(_nickname, _password);
		_createAccountPopUp->close();
		this->show();
		/*if(ok){
			new ErrorBox("Compte créé", "Le compte " + _nickname + " a été créé.");
			_createAccountPopUp->close();
			this->show();
		}
		else{
			new ErrorBox("Compte déjà existant!", "Le compte " + _nickname + " existe déjà.");
		}*/
	}
}
