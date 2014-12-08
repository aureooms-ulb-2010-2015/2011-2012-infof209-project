#ifndef DEF_GUI_CHANGEPASSWORD
#define DEF_GUI_CHANGEPASSWORD

#include <QDialog>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <string>

#include "../GameServerUI.hpp"
#include "../ErrorBox/ErrorBox.hpp"

using namespace std;


class GUI_ChangePassword : public QDialog{
	Q_OBJECT
	
private:
	GameServerUI* _gameServ;
	
   	QGridLayout* _cp_layout;
   	QLabel* _cp_text;
   	
   	QLabel* _cp_oldPass;
   	QLabel* _cp_newPass;
   	
   	QLineEdit* _cp_oldPassEdit;
   	QLineEdit* _cp_newPassEdit;

   	QPushButton* _cp_buttonConfirm;	

public:
	QPushButton* getCp_buttonConfirm();
	QLineEdit* getCp_oldPassEdit();
	QLineEdit* getCp_newPassEdit();
	
	GUI_ChangePassword(GameServerUI* GameServ);
	
public slots:
	void s_ChangePass();

};
#endif
