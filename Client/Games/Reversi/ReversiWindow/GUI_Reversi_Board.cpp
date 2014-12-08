#include "GUI_Reversi_Board.h"
#include "GUI_Reversi_Board_Grid.h"
#include "../h/ReversiBlackPlayer.h"
#include "../h/ReversiWhitePlayer.h"
#include "../h/ReversiMove.h"
#include <QtGlobal>

GUI_Reversi_Board::GUI_Reversi_Board(GameServer* server):Reversi(server,new GUI_Reversi_Board_Grid()){

	QObject::connect(this,SIGNAL(data_received_signal(QString)),
					this,SLOT(data_received_slot(QString)),Qt::QueuedConnection
	);
	
	QObject::connect(this,SIGNAL(emph_clickable_signal()),
					this,SLOT(emph_clickable_slot()),Qt::QueuedConnection
	);
	
	QObject::connect(this,SIGNAL(end_active_turn_signal()),
					this,SLOT(end_active_turn_slot()),Qt::QueuedConnection
	);

	for (unsigned short int i = 0; i<8; i++){
		for (unsigned short int j = 0; j<8; j++){
			QObject::connect(((GUI_Reversi_Board_Grid*)this->board())->_grid[i][j],
				SIGNAL(clicked(unsigned short int,unsigned short int)),
				this,
				SLOT(click_at(unsigned short int,unsigned short int))
			);
		}
	}
	cout << "Clic linké" << endl;

	for (unsigned short int i = 0; i<8; i++){
		for (unsigned short int j = 0; j<8; j++){
			this->_pieces.push(new GUI_Reversi_Piece());
		}
	}
	cout << "Pièces ajoutées" << endl;
	
	this->players()->push_back(new ReversiBlackPlayer());
	this->players()->push_back(new ReversiWhitePlayer());


	cout << "Joueurs ajoutées" << endl;

	this->c_board()->addPiece(3,3,&this->_pieces.top()->setBlack());
	this->_pieces.pop();
	this->c_board()->addPiece(3,4,&this->_pieces.top()->setWhite());
	this->_pieces.pop();
	this->c_board()->addPiece(4,3,&this->_pieces.top()->setWhite());
	this->_pieces.pop();
	this->c_board()->addPiece(4,4,&this->_pieces.top()->setBlack());
	this->_pieces.pop();

	cout << "Pièces centrales ajoutées" << endl;

	cout << "Jeu initialisé" << endl;

	this->setFixedSize(500,500);
	this->setStyleSheet("QWidget { background-color: #145E0D; }");
	this->setLayout((GUI_Reversi_Board_Grid*)(this->board()));
}


void GUI_Reversi_Board::runActiveTurn(){
	if(this->cannotPlay((ReversiPlayer*)this->currentPlayer())){
		this->displayMessage("Il n'y a aucune case jouable dans votre couleur.");
		emit end_active_turn_signal();
	}
	else{
		emit emph_clickable_signal();
	}
}

void GUI_Reversi_Board::emph_clickable_slot(){
	for (unsigned short int i = 0; i<8; i++){
		for (unsigned short int j = 0; j<8; j++){
			GUI_Reversi_Box* box = ((GUI_Reversi_Board_Grid*)this->board())->_grid[i][j];
			if(this->c_board()->validBox(i,j,(ReversiPlayer*)this->currentPlayer())){
				box->clickable();
			}
		}
	}
}

void GUI_Reversi_Board::endActiveTurn(){
	for (unsigned short int i = 0; i<8; i++){
		for (unsigned short int j = 0; j<8; j++){
			((GUI_Reversi_Board_Grid*)this->board())->_grid[i][j]->notClickable();
		}
	}
	Reversi::endActiveTurn();
}

void GUI_Reversi_Board::end_active_turn_slot(){
	this->endActiveTurn();
}

void GUI_Reversi_Board::click_at(unsigned short int column,unsigned short int row){
		ReversiMove* move= new ReversiMove(column,row,this->id());
		this->handleMove(move);
		delete move;
}

void GUI_Reversi_Board::refresh(Request* request){

	QString data = QString::fromStdString(request->getAttributes()[0]);
	cout << "DATAS : " << data.toStdString() << endl;
	emit data_received_signal(data);
}

void GUI_Reversi_Board::refresh(string data){
	if(data != "!!!" && data != "."){
		Move* move = this->parseMove(data);
		this->makeMove(move);
		delete move;
	}
	this->displayTurn();
}

void GUI_Reversi_Board::data_received_slot(QString data){
	this->refresh(data.toStdString());
	cout << "DATAR : " << data.toStdString() << endl;
}

void GUI_Reversi_Board::paintEvent(QPaintEvent * event){
	cout << "paintEvent" << endl;
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
