#ifndef DEF_GUI_USERSLISTWIDGET
#define DEF_GUI_USERSLISTWIDGET

#include <QListWidget>
#include <string>
#include <vector>
#include "../../../GameServerUI.hpp"
#include "../GamePage/GUI_Bet.hpp"
#include "../../Games/GamePlayer.hpp"

using namespace std;

class GUI_UsersListWidget : public QListWidget{
	Q_OBJECT
	public :
		GUI_UsersListWidget(QWidget* parent);
		void BuildList(string list);
		void UpdatePL(GameServerUI* gameServ);
};
#endif
