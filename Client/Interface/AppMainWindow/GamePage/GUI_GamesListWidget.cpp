#include "GUI_GamesListWidget.hpp"

using namespace std;

GUI_GamesListWidget::GUI_GamesListWidget(QWidget* parent, vector<GameInfos>* games) : QListWidget(parent){
	this->BuildList(games);
}

void GUI_GamesListWidget::BuildList(vector<GameInfos>* games){
	ostringstream game;
	game.str("");
	vector<GameInfos>::iterator tmp;
	QListWidgetItem* title = new QListWidgetItem("Jeux en attente de joueurs\nID\tNom de la partie\tType de partie\t Nombre de joueurs");
	title->setFlags(Qt::NoItemFlags);
	this->addItem(title);
	for (tmp = games->begin(); tmp != games->end(); ++tmp) {
		if (tmp->getNumberOfPlayers() != tmp->getRequiredPlayers()){
			if (tmp->getType() != "Backgammon"){
				game << tmp->getId() << "\t" << tmp->getName() << "\t" << tmp->getType() << "\t\t" << tmp->getNumberOfPlayers() << "/" << tmp->getRequiredPlayers();
			}
			else{
				game << tmp->getId() << "\t" << tmp->getName() << "\t" << tmp->getType() << "\t" << tmp->getNumberOfPlayers() << "/" << tmp->getRequiredPlayers();
			}		
			this->addItem(QString(game.str().c_str()));
			game.str("");
		}
	}
	title = new QListWidgetItem("\nJeux complets\nID\tNom de la partie\tType de partie\t Nombre de joueurs");
	title->setFlags(Qt::NoItemFlags);
	this->addItem(title);
	for (tmp = games->begin(); tmp != games->end(); ++tmp) {
		if (tmp->getNumberOfPlayers() == tmp->getRequiredPlayers()){
			if (tmp->getType() != "Backgammon"){
				game << tmp->getId() << "\t" << tmp->getName() << "\t" << tmp->getType() << "\t\t" << tmp->getNumberOfPlayers() << "/" << tmp->getRequiredPlayers();
			}
			else{
				game << tmp->getId() << "\t" << tmp->getName() << "\t" << tmp->getType() << "\t" << tmp->getNumberOfPlayers() << "/" << tmp->getRequiredPlayers();
			}		
			this->addItem(QString(game.str().c_str()));
			game.str("");
		}
	}
}

void GUI_GamesListWidget::updateGL(vector<GameInfos>* games){
	this->clear();
	BuildList(games);
}
