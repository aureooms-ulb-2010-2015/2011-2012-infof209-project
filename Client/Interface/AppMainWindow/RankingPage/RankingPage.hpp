#ifndef DEF_RANKINGPAGE
#define DEF_RANKINGPAGE

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>

#include "../GameServerUI.hpp"
#include "../Server.hpp"
#include "../Page.hpp"
#include "GUI_RankingWidget.hpp"

class RankingPage : public Page {
	Q_OBJECT
	private:
/* ----- Global ----- */
    QWidget* _rankingWidget;
   	QGridLayout* _rankingLayout;

	QTabWidget* _rankingTab;
	GUI_RankingWidget* _globalRanking;
	GUI_RankingWidget* _friendsRanking;
	
    QPushButton* _r_buttonHome;
		
	public:
	void updateRankings();

/* ----- Getters ----- */
    QWidget* getRankingWidget();
    QPushButton* getR_buttonHome();
	
/* ----- Setters ----- */
	void setRankingWidgetVisible(bool visible);

/* ----- Constructeur ----- */	
	RankingPage(string Nickname, GameServerUI* GameServ, QWidget* GlobalWidget, QVBoxLayout* GlobalLayout);

};
#endif
