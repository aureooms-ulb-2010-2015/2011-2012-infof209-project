#include "GUI_Bet.hpp"


GUI_Bet::GUI_Bet(GameServerUI* gameServ): Bet(gameServ){
	_message = new QMessageBox(this);
	_message->setWindowTitle("Statut des mises");
	connect(this, SIGNAL(si_askAmount()), this, SLOT(s_askAmount()));
	connect(this, SIGNAL(si_askValidation()), this, SLOT(s_askValidation()));
}

void GUI_Bet::displayWait(bool visible){
	_message->setText("En attende des autres joueurs...");
	_message->setVisible(visible);
}

void GUI_Bet::displayValid(bool visible){
	_message->setText("Tout le monde à accepté les mises !");
	_message->setVisible(visible);
}

void GUI_Bet::displayNotValid(bool visible){
	_message->setText("Les mises n'ont pas été acceptées par tous les joueurs");
	_message->setVisible(visible);
}

void GUI_Bet::route(Request * request){
    if(request->getName()=="askAmount"){
        emit si_askAmount();
    }
    else if(request->getName() == "addBet"){
		addBetToList(request);
    }
    else if(request->getName() == "validate"){
        emit si_askValidation();
    }
}

void GUI_Bet::addBetToList(Request* request){
	if (request->getAttributes().size() >= 2)
		this->listOfBets->push_back(make_pair(request->getAttributes()[0],request->getAttributes()[1]));
}

void GUI_Bet::displayBets(){
}

// === Slots ==========================================================
void GUI_Bet::s_askAmount(){
	this->listOfBets->clear();
	_askWidget = new QDialog(this);
   	_askLayout = new QVBoxLayout(_askWidget);
   	_askText = new QLabel("Que voulez vous miser ?", _askWidget);
   	_askSpinBox = new QSpinBox(_askWidget);
   	_askSpinBox->setMaximum(99999);
   	_confirmBet = new QPushButton("Miser", _askWidget);
   	
   	_askLayout->addWidget(_askText);
   	_askLayout->addWidget(_askSpinBox);
   	_askLayout->addWidget(_confirmBet);
   	_askWidget->setLayout(_askLayout);
   	_askWidget->setVisible(true);
   	connect(_confirmBet, SIGNAL(clicked()), this, SLOT(s_confirmBet()));
}

void GUI_Bet::s_askValidation(){
	_message->setVisible(false);
	_dispWidget = new QDialog(this);
	_dispLayout = new QGridLayout(_dispWidget);
	_dispText = new QLabel("Voici les mises des autres joueurs,\n acceptez vous de jouer la partie?", _dispWidget);
	_dispBets = new QListWidget(_dispWidget);
	for(unsigned int i = 0; i < this->listOfBets->size();++i){
		string bet = (*listOfBets)[i].first +" a misé " +(*listOfBets)[i].second;
		_dispBets->addItem(QString::fromStdString(bet));
	}
	_validBets = new QPushButton("Accepter", _dispWidget);
	_cancelBets = new QPushButton("Refuser", _dispWidget);
   	
	_dispLayout->addWidget(_dispText, 0, 0);
	_dispLayout->addWidget(_dispBets, 1, 0);
	_dispLayout->addWidget(_validBets, 2, 0);
	_dispLayout->addWidget(_cancelBets, 2, 1);
	_dispWidget->setLayout(_dispLayout);
	_dispWidget->setVisible(true);
	
   	connect(this->_validBets, SIGNAL(clicked()), this, SLOT(s_validBets()));
   	connect(this->_cancelBets, SIGNAL(clicked()), this, SLOT(s_cancelBets()));
}

void GUI_Bet::s_confirmBet(){
	Request request(this->getGameServer());
	int amount = _askSpinBox->value();
	if (amount > 0){
		ostringstream temp;
		temp << amount;
		request.makeRequest("BET",temp.str().c_str());
		request.flush();
		delete(_askWidget);
		displayWait(true);
	}
	else{
		new ErrorBox("Mise trop faible!", "Vous devez au moins miser 1 point.");
	}
}

void GUI_Bet::s_validBets(){
	Request request(this->getGameServer());
	request.makeRequest("BET","validate");
	request.addAttribute("true");
	request.flush();
	_dispWidget->setVisible(false);
	emit si_mustUpdate();
}

void GUI_Bet::s_cancelBets(){
	Request request(this->getGameServer());
	request.makeRequest("BET","validate");
	request.addAttribute("false");
	request.flush();
	_dispWidget->setVisible(false);	
}

