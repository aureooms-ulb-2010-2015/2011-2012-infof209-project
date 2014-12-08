

#include <QDebug>
#include <QString>

#include "LudoWindow.hpp"



LudoWindow::LudoWindow(int nbPlayers, GameServer* server) : Ludo(nbPlayers,server,new UiLudoBoard(nbPlayers))
{
    QObject::connect(this,SIGNAL(runActiveTurn_signal()),this,SLOT(runActiveTurn_slot()),Qt::QueuedConnection);

	
	
    for (int i = 0 ; i<nbPlayers ; i++){

            QString owner;
            owner.setNum(i);
            UiLudoPlayer* newPlayer = new UiLudoPlayer(owner,i);
            this->players()->push_back(newPlayer);
    }
	


    this->c_getMainBoard()->init(this->players());
    
    this->setFixedSize(508,508);

    this->setLayout( this->c_getMainBoard() );
    this->setDice(6);
    for (int i=0; i<nbPlayers*4;i++){
		
        connect( this->c_getMainBoard()->getHorse(i), SIGNAL( clicked(int,int) ), this, SLOT( horseClicked(int,int) ) );
        connect( this->c_getMainBoard()->getHorse(i), SIGNAL( IWantMyGhostToBeShown(int)), this, SLOT( ghostRequest(int) ) );

    }



}


void LudoWindow::DisplayPlayablePieces(){

    for (int i=0; i<4; i++){

        if(this->_isPlayablePieces[i]){
            this->c_getMainBoard()->makeItRun(i,this->id());
        }
        else{
            this->c_getMainBoard()->stopIt(i,this->id());
        }

    }


}

void LudoWindow::runActiveTurn(){

	emit runActiveTurn_signal();
}


void LudoWindow::runActiveTurn_slot(){
	
	this->setDice(this->rollDice());
	qDebug()<<"-------------------------vous avez fait "<<this->getDice();
	for (int i=0;i<4;i++){
        this->_isPlayablePieces[i]=this->playable(this->getPlayer(this->id())->getPiece(i));
	}
	this->DisplayPlayablePieces();
	if (!this->YouCanPlay()){
		this->endActiveTurn();
	}
	
	
}

void LudoWindow::endActiveTurn(){
	this->c_getMainBoard()->makeSum();
	this->c_getMainBoard()->stopThem();
	Game::endActiveTurn();
	}


void LudoWindow::horseClicked(int start, int piece){
    UiLudoPiece * horse =this->c_getMainBoard()->getHorse((this->id()*4)+piece);
    delete (horse->getGhost());
    horse->resetClickCount();

    this->c_getMainBoard()->ghostBuster();
    horse->resetClickCount();
    

    int finish=0;
    if (start==-1){
        finish = ((52-(this->id() * 13))%52);
    }
    else{
            finish=start+this->getDice();
    }
    LudoMove * move = new LudoMove(start,finish,piece,horse->getPieceColor());

	this->handleMove(move);
	if(!this->endOfTurn()){
		this->c_getMainBoard()->stopThem();
		this->runActiveTurn();
	}
	
}



void LudoWindow::ghostRequest(int piece){


    Ghost* ghost = this->c_getMainBoard()->displayMyGhost(this->getDice(),piece,this->id());

    this->c_getMainBoard()->addWidget(ghost, ghost->getGridI(),ghost->getGridJ());

}

UiLudoBoard* LudoWindow::c_getMainBoard(){

    return (UiLudoBoard*)Ludo::c_getMainBoard();
}




bool LudoWindow::YouCanPlay(){
	
	return (this->_isPlayablePieces[0] || this->_isPlayablePieces[1] || this->_isPlayablePieces[2] || this->_isPlayablePieces[3]);
}	























