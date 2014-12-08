#include "GUI_FriendsListWidget.hpp"

using namespace std;

GUI_FriendsListWidget::GUI_FriendsListWidget(QWidget* parent, vector<Player>* friends) : QListWidget(parent){
	this->BuildFriendsList(friends);
}

void GUI_FriendsListWidget::BuildFriendsList(vector<Player>* friends){
	ostringstream friend_;
	friend_.str("");
	vector<Player>::iterator tmp;
	QListWidgetItem* title = new QListWidgetItem("\0Liste d'amis\nNom\t\tPoints\n");
	title->setFlags(Qt::NoItemFlags);
	this->addItem(title);
	for (tmp = friends->begin(); tmp != friends->end(); ++tmp) {
		friend_ << tmp->getName() << "\t\t" << tmp->getPoints();
		this->addItem(QString(friend_.str().c_str()));
		friend_.str("");
	}
	this->sortItems();
}

void GUI_FriendsListWidget::updateF(vector<Player>* friends){
	this->clear();
	BuildFriendsList(friends);
}

