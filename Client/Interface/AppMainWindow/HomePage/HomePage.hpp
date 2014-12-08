#ifndef DEF_HOMEPAGE
#define DEF_HOMEPAGE
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <string>

#include "../Page.hpp"

class HomePage : public Page{
	Q_OBJECT
private:
/* ----- Global Widget ----- */
    QWidget* _homeWidget;
   	QVBoxLayout* _homeLayout;
   	
/* ----- Label Welcome ----- */
	QLabel* _h_welcomeLabel;
	
/* ----- Widget Boutons ----- */
    QWidget* _h_buttonWidget;
   	QHBoxLayout* _h_buttonLayout;
   	
    QPushButton* _h_buttonGames;
    QPushButton* _h_buttonRanking;
    QPushButton* _h_buttonFriends;
	QPushButton* _h_buttonQuit;	
	
public:
/* ----- Getters ----- */
    QWidget* getHomeWidget();	
	QPushButton* getH_buttonGames();
	QPushButton* getH_buttonRanking();
	QPushButton* getH_buttonFriends();
	QPushButton* getH_buttonQuit();
	
/* ----- Setters ----- */
void setHomeWidgetVisible(bool visible);

/* ----- Constructeur ----- */
	HomePage(string Nickname, GameServerUI* GameServ, QWidget* GlobalWidget, QVBoxLayout* GlobalLayout);
};
#endif
