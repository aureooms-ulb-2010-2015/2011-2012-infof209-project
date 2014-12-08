#ifndef DEF_GUI_RANKINGWIDGET
#define DEF_GUI_RANKINGWIDGET

#include <QListWidget>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include "../../../Player.hpp"

using namespace std;

class GUI_RankingWidget : public QListWidget{
	Q_OBJECT
	public :
		GUI_RankingWidget(QWidget* parent, vector<Player>* players);
		void BuildRanking(vector<Player>* players);
		void updateR(vector<Player>* players);
};
#endif
