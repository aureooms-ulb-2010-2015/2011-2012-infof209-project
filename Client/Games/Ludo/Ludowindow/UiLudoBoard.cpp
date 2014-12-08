
#include "UiLudoBoard.hpp"
#include<QDebug>

UiLudoBoard::UiLudoBoard(int nbPlayers)
{

    _nbPlayers=nbPlayers;
    _informationDesk = new InformationDesk;
    this->setSpacing(1);
    this->letsPutSomeColor();

    QString owner;




}

void UiLudoBoard::init(vector<GamePlayer *> * players){
    LudoBoard::init(players);

    for(int i=0; i<players->size();i++){
        for (int j =0;j<4;j++){
			//qDebug()<<i<<" "<<j;

            _horses[(i*4)+j]=(UiLudoPiece*)this->c_getPlayer(i)->getPiece(j);
        }
    }
    
    for (int i =0;i<players->size()*4;i++){

        this->putHorse((QLabel*)_horses[i], _homes[i]);//!!! si un jour tu décommentes cette ligne...je te souhaite bon courage
    }

}

void UiLudoBoard::makeSum(){
	
	
	qDebug()<<"reqPlayers "<<this->_nbPlayers;
	for(int i = 0; (i < this->_nbPlayers); ++i){

			qDebug()<<"*********************************i= "<<i<<" SUM= "<<this->c_getPlayer(i)->makePosSum();
	}
	
	

}




LudoPlayer* UiLudoBoard::c_getPlayer(int i ){
    return ((UiLudoPlayer*) this->_listPlayers->at(i));

}

void UiLudoBoard::letsPutSomeColor(){


    int k=0,  voidCounter=0  ;
    int blueCount=12, yellowCount=8, redCount=0, greenCount=4;
    int blueBCount=15, yellowBCount=10, redBCount=0, greenBCount=5;
    for (int i=0; i<15;++i){
        for (int j=0;j<15;++j){


            /*TESTS HOMES*/
            if(_informationDesk->isBlueHome(i,j) or _informationDesk->isGreenHome(i,j) or _informationDesk->isRedHome(i,j) or _informationDesk->isYellowHome(i,j) ){

                if ( _informationDesk->isBlueHome(i,j) ){

                    _homes[blueCount]=new UiOwnedCell(_informationDesk->getBluePath(),3);
                    _homes[blueCount]->init(i,j,blueCount);
                    this->addWidget(_homes[blueCount], i, j);
                    blueCount++;

                }
                else if ( _informationDesk->isGreenHome(i,j) ){

                    _homes[greenCount]=new UiOwnedCell(_informationDesk->getGreenPath(),1);
                    _homes[greenCount]->init(i,j,greenCount);
                    this->addWidget(_homes[greenCount], i, j);
                    greenCount++;


                }
                else if ( _informationDesk->isRedHome(i,j) ){

                    _homes[redCount]=new UiOwnedCell(_informationDesk->getRedPath(),0);
                    _homes[redCount]->init(i,j,redCount);
                    this->addWidget(_homes[redCount], i, j);
                    redCount++;

                }
                else if ( _informationDesk->isYellowHome(i,j) ){

                    _homes[yellowCount]=new UiOwnedCell(_informationDesk->getYellowPath(),2);
                    _homes[yellowCount]->init(i,j,yellowCount);
                    this->addWidget(_homes[yellowCount], i, j);
                    yellowCount++;
                }



           }


            /*TEST BOARD*/


            else if ( _informationDesk->northSide(i,j) or _informationDesk->westSide(i,j) or _informationDesk->southSide(i,j) or _informationDesk->eastSide(i,j) )  {


                UiLudoCell* cell=new UiLudoCell();



                if(cell->findMyColor(i,j,k)){//si la cellule est un Bridge
                    UiOwnedCell* bridge= (UiOwnedCell*)cell;
                    if (_informationDesk->northSide(i,j)){
                        bridge->setOwnerId(0);
                        bridge->init(i,j,k);
                        _bridges[redBCount]=bridge;
                        this->addWidget(_bridges[redBCount], i, j);
                        redBCount++;
                    }
                    else if (_informationDesk->westSide(i,j)){
                        bridge->setOwnerId(1);
                        bridge->init(i,j,k);
                        _bridges[greenBCount]=bridge;
                        this->addWidget(_bridges[greenBCount], i, j);
                        greenBCount++;
                    }
                    else if (_informationDesk->southSide(i,j)){
                        bridge->setOwnerId(2);
                        bridge->init(i,j,k);
                        _bridges[yellowBCount]=bridge;
                        this->addWidget(_bridges[yellowBCount], i, j);
                        yellowBCount++;
                    }
                    else if (_informationDesk->eastSide(i,j)){
                        bridge->setOwnerId(3);
                        bridge->init(i,j,k);
                        _bridges[blueBCount]=bridge;
                        this->addWidget(_bridges[blueBCount], i, j);
                        blueBCount++;
                    }


                }
                else{

                    _cells[k]=cell;
                    _cells[k]->init(i,j,k);
                     this->addWidget(_cells[k], i, j);
                     k++;
                }
            }



            else{//la case ne fait pas partie du plateau

               _void[voidCounter]=new UiVoidCell(_informationDesk->getVoidPath());
               _void[voidCounter]->init(i,j,voidCounter);
               this->addWidget(_void[k], i, j);
               voidCounter++;
            }

        }
    }


}


void UiLudoBoard::putHorse(QLabel* horse, UiLudoCell* cell){

   

    this->addWidget(horse, cell->getGridi(), cell->getGridj());
    

}

void UiLudoBoard::moveHorse(UiLudoPiece* horse, UiLudoCell* cell){

    this->removeWidget(horse);
    

    this->addWidget(horse, cell->getGridi(), cell->getGridj());

}






void UiLudoBoard::backInHome(int piecenb, int owner){

    
    UiLudoPiece* Uipiece =(UiLudoPiece*)this->c_getPlayer(owner)->getHisPieces()->at(piecenb);
    LudoBoard::backInHome(Uipiece->getPosition());
    UiOwnedCell* cell = _homes[(owner*4)+piecenb];
    this->moveHorse(Uipiece,cell);

}

void UiLudoBoard::stopIt(int horse, int owner){

  ( (UiLudoPiece*) _horses[(owner*4)+horse])->stop();

}

void UiLudoBoard::makeItRun(int horse, int owner){
   ((UiLudoPiece*) _horses[(owner*4)+horse])->run();

}

void UiLudoBoard::stopThem(){
    for (int i=0; i<_nbPlayers*4; i++){
        ((UiLudoPiece*)_horses[i])->stop();
    }


}

void UiLudoBoard::showCells(){
    int i =0;
    while (i<52) {
        qDebug()<<" case number="<<_cells[i]->getCaseNumber()<<" i="<<_cells[i]->getGridi()<<" j="<<_cells[i]->getGridj();
        i++;
     }

}


UiLudoCell* UiLudoBoard::getCell(int pos){
    int i =0;
    while (i<52){
        if (_cells[i]->getCaseNumber()==pos){
                break;
        }
        else{
            i++;
        }
     }
    return _cells[i];

}

UiOwnedCell* UiLudoBoard::getBridgeCell(int pos,int owner){
	
    
    return _bridges[(owner*5)+pos];
   

}

UiOwnedCell* UiLudoBoard::getHomeCell(int pos,int owner){
   
    return _homes[(owner*4)+pos];
    

}



void UiLudoBoard::setBoard(int pos, LudoPiece * piece){
    UiLudoPiece * Uipiece=( UiLudoPiece*) piece;

    LudoBoard::setBoard(pos,piece);


    UiLudoCell* cell =this->getCell(pos);
    this->moveHorse(Uipiece,cell);



}

void UiLudoBoard::setBridge(int pos, LudoPiece * piece){
    UiLudoPiece * Uipiece=( UiLudoPiece*) piece;
    LudoBoard::setBridge(pos,piece);
    UiOwnedCell* cell=this->getBridgeCell(pos,piece->getPieceColor());
    this->putHorse(Uipiece,cell);

}



void UiLudoBoard::setHome(int pos, LudoPiece * piece){
    UiLudoPiece * Uipiece=(UiLudoPiece*) piece;
    LudoBoard::setHome(pos,piece);
    UiOwnedCell* cell=this->getHomeCell(pos,piece->getPieceColor());
    this->putHorse(Uipiece,cell);


}






UiLudoPiece* UiLudoBoard::c_getPieceInCell(int pos){return (UiLudoPiece*) this->getPieceInCell(pos);}


UiLudoPiece* UiLudoBoard::c_getPlayerBridgeBox(int PlayerID, int i){return (UiLudoPiece*) this->getPlayerBridgeBox(PlayerID,i);}


UiLudoPiece* UiLudoBoard::findHorse(int owner,int piece){


    int i=owner*4;

    while (i<(owner*4)+4){
        if (((UiLudoPiece*)_horses[i])->getNumber()==piece){

                break;
        }
        else{
            i++;
        }
     }
    return ((UiLudoPiece*)_horses[i]);

}


UiLudoPiece* UiLudoBoard::getHorse(int i){return _horses[i];}


Ghost* UiLudoBoard::displayMyGhost(int dice, int piece, int id){

    int  start=-2, jumpOnBridge = ((52-(id*13))-2) ,finish  = 0;

    UiLudoCell* theCell;

    UiLudoPiece* horse = this->findHorse(id, piece);
    start=horse->getPosition();
    finish = start+dice;

	if (start>=jumpOnBridge){
	
		if (start>=100){//(	bridge bridge)

        	theCell=this->getBridgeCell(finish-jumpOnBridge-1,id);
		}
	
		else if (start==jumpOnBridge){//(board bridge)

			theCell=this->getBridgeCell((finish-jumpOnBridge-1),id);
		}
	
		else{//board board

			finish=finish%52;
			theCell=this->getCell(finish);
		}
	
	}
	
	else{
	
		if (start==-1){//home board

			theCell=this->getCell(((52-(id * 13))%52));
		}
		
		else if (finish>jumpOnBridge){//(board bridge)

			theCell=this->getBridgeCell(finish-jumpOnBridge-1,id);
			
		}
		
		else{  //board board

			finish=finish%52;
			theCell=this->getCell(finish);
		
		
		}
	
	}
	Ghost* ghost=new Ghost(theCell->getGridi(),theCell->getGridj());
    horse->setGhost(ghost);
    return ghost;

}







void UiLudoBoard::ghostBuster(){
	for (int i=0;i<_nbPlayers*4;i++){
		if (_horses[i]->getClickCount()>0){

			_horses[i]->resetClickCount();
			delete (_horses[i]->getGhost());
		}
	}
}


UiLudoPiece* UiLudoBoard::c_getBoardBox(int i){


    return (UiLudoPiece*)LudoBoard::c_getBoardBox(i);


}

UiLudoPiece** UiLudoBoard::getHorses(){
    return _horses;

}


