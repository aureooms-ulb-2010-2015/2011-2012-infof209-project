#ifndef DEF_LOGINPAGE
#define DEF_LOGINPAGE
#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QDialog>
#include <QLineEdit>
#include <QPushButton>

#include "../GameServerUI.hpp"
#include "../ListenerServer.hpp"
#include "../AppMainWindow/AppMainWindow.hpp"
#include "../ErrorBox/ErrorBox.hpp"	
#include "../../../Common/Request.hpp"

class LoginPage: public QWidget
{
    Q_OBJECT
    
private:
/* ----------- Attributs --------- */   
	GameServerUI* _gameServ;
	ListenerServer* _listenerServ;
	
	QGridLayout* _globalLayout;
	
   	QPushButton* _buttonCreateAccount;
    QPushButton* _buttonValidation;
    
   	QLabel* _nicknameLabel;
   	QLabel* _passwordLabel;
   	QLabel* _ipLabel;
    	
    QLineEdit* _nicknameEdit;
   	QLineEdit* _passwordEdit;
   	QLineEdit* _ipEdit;
   	
   	string _nickname;
   	string _password;
   	string _ip;
   	
/* ----------- Pop-Up Creer Compte --------- */
   	QDialog* _createAccountPopUp;
   	QGridLayout* _ca_layout;
   	QLabel* _ca_text;
   	
   	QPushButton* _ca_buttonCreate;
   	QLabel* _ca_nickname;
   	QLabel* _ca_password;
   	
   	QLineEdit* _ca_nicknameEdit;
   	QLineEdit* _ca_passwordEdit;
   	
    	
public slots:
  	void s_validation();
  	void s_createAccount();
  	void s_create();
  		
public:
	void getIPEdit();
    LoginPage(GameServerUI* GameServ);
    ~LoginPage();
};
#endif
