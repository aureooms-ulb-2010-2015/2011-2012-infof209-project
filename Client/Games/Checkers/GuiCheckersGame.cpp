#include "GuiCheckersGame.hpp"

GuiCheckersGame::GuiCheckersGame(GameServer* server) : CheckersGame(server,new GuiCheckersBoard),QWidget(){

	
	QObject::connect(this,SIGNAL(data_received_signal(QString)),
					this,SLOT(data_received_slot(QString)),Qt::QueuedConnection
	);


	this->setFixedSize(500,600);
	this->_principalLayout = new QVBoxLayout();

	this->_controlPanel = new QLabel("Bienvenue dans le jeu de dames");

	this->_principalLayout->addLayout(this->c_board());
	this->c_board()->initBoard();

	this->_principalLayout->addWidget(this->_controlPanel);
	this->setLayout(this->_principalLayout);
	this->firstXmove = -1;
	this->firstYmove = -1;
	this->secondXmove = -1;
	this->secondYmove = -1;
	this->isClickEnable = false;
}

GuiCheckersGame::~GuiCheckersGame(){

}

GuiCheckersBoard* GuiCheckersGame::c_board(){
	return (GuiCheckersBoard*)(this->board());

}
void GuiCheckersGame::mousePressEvent(QMouseEvent * ev)
{
	if (this->isClickEnable){
		if(ev->x() <= 500 && ev->y() <= 500)
		{
			if (this->firstXmove == -1 && this->firstYmove == -1){
				this->firstXmove = ev->x()/50;
				this->firstYmove = ev->y()/50;
				this->c_board()->selectPiece(firstYmove,firstXmove);
			}
			else{
				if (validateMovement(this->firstYmove,this->firstXmove,ev->y()/50,ev->x()/50,this->c_player())){
				    CheckersMove* move = new CheckersMove(this->firstYmove,this->firstXmove,ev->y()/50,ev->x()/50);
					this->handleMove(move);

				    this->c_board()->checkForKings();
				    if (this->endOfTurn())
						cout<<"Fin du tour"<<endl;
				}
				else{
				    this->c_board()->unselectPiece(this->firstYmove,this->firstXmove);
				}
				this->firstXmove = -1;
				this->firstYmove = -1;
			}
		}
	}
}

void GuiCheckersGame::runActiveTurn(){

	
	if (this->winner() == -1){
		this->isClickEnable = true;
		if (this->isCapturePossible(this->c_player())){
			this->_controlPanel->setText("Vous devez faire une prise");
		}
		else{
			this->_controlPanel->setText("C'est votre tour");
		}
	}

}

void GuiCheckersGame::endActiveTurn(){
	this->_hasCapture = false;
	this->isClickEnable = false;
	this->_controlPanel->setText("Ce n'est pas votre tour");
	CheckersGame::endActiveTurn();
}

void GuiCheckersGame::refresh(Request* request){

	QString data = QString::fromStdString(request->getAttributes()[0]);
	cout << "DATAS : " << data.toStdString() << endl;
	emit data_received_signal(data);
}

void GuiCheckersGame::refresh(string data){
	if(data != "!!!" && data != "."){
		Move* move = this->parseMove(data);
		this->makeMove(move);
		delete move;
	}
	this->displayTurn();
}

void GuiCheckersGame::data_received_slot(QString data){
	this->refresh(data.toStdString());
	cout << "DATAR : " << data.toStdString() << endl;
}
