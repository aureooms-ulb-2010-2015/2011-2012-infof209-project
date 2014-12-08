#include "GUI_UsersListWidget.hpp"

using namespace std;

GUI_UsersListWidget::GUI_UsersListWidget(QWidget* parent) : QListWidget(parent){
}

void GUI_UsersListWidget::BuildList(string list){
	string playersList = "";
	QListWidgetItem* title = new QListWidgetItem("Joueurs\t\t\tMises\n");
	this->addItem(title);
	title->setFlags(Qt::NoItemFlags);
	QListWidgetItem* listplayers = new QListWidgetItem(QString(list.c_str()));	
	this->addItem(listplayers);
	listplayers->setFlags(Qt::NoItemFlags);	
}

void GUI_UsersListWidget::UpdatePL(GameServerUI* gameServ){
	this->clear();
	string betList = "";
	int totalBet = 0;
	for(int unsigned i=0; i < (gameServ->getBet()->getListOfBets())->size() ;i++){ 
		betList += (*(gameServ->getBet()->getListOfBets()))[i].first + "\t\t\t" + (*(gameServ->getBet()->getListOfBets()))[i].second + "\n";
		totalBet += atoi((*(gameServ->getBet()->getListOfBets()))[i].second.c_str());
	}
	ostringstream totalBet2;
	totalBet2 << totalBet;
	betList += "\nTotal:\t\t\t" + totalBet2.str() + "\n";
	cout << betList << endl;
	BuildList(betList);
}
