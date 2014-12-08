#ifndef DEF_FRIENDSPAGE
#define DEF_FRIENDSPAGE
#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QListWidget>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QPushButton>
#include <QIntValidator>
#include <string>

#include "../Page.hpp"
#include "GUI_FriendsListWidget.hpp"

class FriendsPage : public Page{
	Q_OBJECT
private:
/* ----- Global ----- */
    QWidget* _friendsWidget;
   	QGridLayout* _friendsLayout;

/* ----- Label Amis ----- */
	QLabel* _f_friendsLabel;

/* ----- Liste Amis ----- */
	GUI_FriendsListWidget* _f_friendsList;
	
/* ----- Nouvel Ami ----- */
	QLabel* _f_newFriendLabel;
	QLineEdit* _f_newFriendEdit;
	
	QLabel* _f_displayMessage;
	
/* ----- Widget Boutons ----- */		
    QWidget* _f_buttonWidget;
   	QVBoxLayout* _f_buttonLayout;

    QPushButton* _f_buttonAdd;
    QPushButton* _f_buttonDelete;
    QPushButton* _f_buttonHome;

/* ----- Widget Don ---- */
    QWidget* _f_giveWidget;
   	QGridLayout* _f_giveLayout;
   	
   	QLabel* _f_giveLabel;
   	QLineEdit* _f_giveEdit;
    QPushButton* _f_buttonGive;
    QIntValidator* _f_giveValidator;
    

public:
/* ----- Getters ----- */
    QWidget* getFriendsWidget();
	GUI_FriendsListWidget* getF_friendsList();
	QLineEdit* getF_newFriendEdit();
    QPushButton* getF_buttonAdd();
    QPushButton* getF_buttonDelete();
    QPushButton* getF_buttonHome();
    QLineEdit* getF_giveEdit();
    QIntValidator* getF_giveValidator();
    QPushButton* getF_buttonGive();
    
/* ----- Setters ----- */
	void setFriendsWidgetVisible(bool visible);
	void setF_DisplayMessage(string message);
	void initF_newFriendEdit();
	
/* ----- Constructeur ----- */    
	FriendsPage(string Nickname, GameServerUI* GameServ, QWidget* GlobalWidget, QVBoxLayout* GlobalLayout);

};
#endif
