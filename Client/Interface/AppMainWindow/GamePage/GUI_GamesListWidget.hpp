#ifndef DEF_GUI_GAMESLISTWIDGET
#define DEF_GUI_GAMESLISTWIDGET

#include <QListWidget>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include "../../../GameInfos.hpp"

using namespace std;

class GUI_GamesListWidget : public QListWidget{
	Q_OBJECT
	public :
		GUI_GamesListWidget(QWidget* parent, vector<GameInfos>* games);
		void BuildList(vector<GameInfos>* games);
		void updateGL(vector<GameInfos>* games);
};
#endif
