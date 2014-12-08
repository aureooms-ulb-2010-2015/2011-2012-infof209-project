#ifndef DEF_GUI_FRIENDSLISTWIDGET
#define DEF_GUI_FRIENDSLISTWIDGET

#include <QListWidget>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include "../../../Player.hpp"

using namespace std;

class GUI_FriendsListWidget : public QListWidget{
	Q_OBJECT
	public :
		GUI_FriendsListWidget(QWidget* parent, vector<Player>* friends);
		void BuildFriendsList(vector<Player>* friends);
		void updateF(vector<Player>* friends);
};
#endif
