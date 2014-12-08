#include "GUI_RankingWidget.hpp"

using namespace std;

GUI_RankingWidget::GUI_RankingWidget(QWidget* parent, vector<Player>* players) : QListWidget(parent){
	this->BuildRanking(players);
	cout << " --------------- CONSTR OK----------------- " << endl;
}

void GUI_RankingWidget::BuildRanking(vector<Player>* players){
	ostringstream player;
	player.str("");
	vector<Player>::iterator tmp;
	QListWidgetItem* title = new QListWidgetItem("\0Nom\t\tPoints\n");
	title->setFlags(Qt::NoItemFlags);
	this->addItem(title);
	for (tmp = players->begin(); tmp != players->end(); ++tmp) {
		player << tmp->getName() << "\t" << tmp->getPoints();
		this->addItem(QString(player.str().c_str()));
		player.str("");
	}
}

void GUI_RankingWidget::updateR(vector<Player>* players){
	this->clear();
	BuildRanking(players);
}
