// Ludo
// Antoine de Wasseige - <Board.hpp>

#include <vector>
#include <string>
#include <iostream>

#include "LudoBoard.hpp"
#include "LudoPiece.hpp"

using namespace std;

// Methodes de _homeList

LudoPiece** LudoBoard::getPlayerHome(int PlayerID){
	return this->_homeList[PlayerID];
}

// Methodes de _bridgeList
LudoPiece** LudoBoard::getPlayerBridge(int PlayerID){
	return this->_bridgeList[PlayerID];
}
LudoPiece* LudoBoard::getPlayerBridgeBox(int PlayerID, int i){
	return this->_bridgeList[PlayerID][i];
}

// Methode _board
LudoPiece*** LudoBoard::getBoard(){
	return (LudoPiece***)this->_board;
}
LudoPiece* LudoBoard::c_getBoardBox(int i){
	return (LudoPiece*)this->getPieceInCell(i);
}
void LudoBoard::setBoard(int i, LudoPiece* piece){
   	
    this->addPiece(i,piece);
        //_board[i][] = piece;
}

// Constructeur/Destructeur

LudoBoard::LudoBoard() : Board(52,0){
}


void LudoBoard::init(vector<GamePlayer*>* ListPlayers){

	int NbPlayers = ListPlayers->size();
	// Initialisation de _listPlayers
	this->_listPlayers = ListPlayers;
	
	// Initialisation de _homeList
	for(int i = 0; i < NbPlayers; i++){
		for (int j = 0; j < 4; j ++){
			
			this->_homeList[i][j] = this->c_getPlayer(i)->getPiece(j);
		}
	}
	// Initialisation de _bridgeList
	for (int k = 0; k < NbPlayers; k++){
		for (int l = 0; l < 6; l++){
			this->_bridgeList[k][l] = NULL;
		}
	}

	// Initalisation de _board
	for (int m = 0; m < 52; m++){
		this->_board[m][0] = NULL;
	}


}

LudoBoard::~LudoBoard(){}

void LudoBoard::display(){}


LudoPlayer* LudoBoard::c_getPlayer(int i){return (LudoPlayer*)(this->_listPlayers->at(i));}

void LudoBoard::setHome(int pos,LudoPiece* piece){
    this->getPlayerHome(piece->getPieceColor())[piece->getNumber()] = piece;
}

void LudoBoard::setBridge(int pos ,LudoPiece* piece){

	
    this->getPlayerBridge(piece->getPieceColor())[pos] = piece;
}



void LudoBoard::eraseFromBoard(int start){
        this->setBoard(start, NULL);
}

void LudoBoard::eraseFromHome(int owner, int piece){
        this->getPlayerHome(owner)[piece]=NULL;
}


void LudoBoard::backInHome(int pos){

        LudoPiece* piece = this->c_getBoardBox(pos);;
        this->setHome(piece->getNumber(),piece);
        piece->setPosition(-1);

}




void LudoBoard::eraseFromBridge(int owner, int pos){

        this->getPlayerBridge(owner)[pos]=NULL;
}




void LudoBoard::moveFromBoardToBridge( int piecenb,int owner, int finish){

        LudoPiece* piece =this->c_getPlayer(owner)->getPiece(piecenb);
		int jumpOnBridge = ((52-(piece->getPieceColor()*13))-2);
        this->setBridge(finish-jumpOnBridge-1,piece);

        piece->setPosition((finish-jumpOnBridge-1)+100);


}

void LudoBoard::moveFromBridgeToBridge(int piecenb,int owner,int finish){
		
        LudoPiece* piece =this->c_getPlayer(owner)->getPiece(piecenb);
        int jumpOnBridge = ((52-(piece->getPieceColor()*13))-2);
        this->setBridge(finish-100,piece);

        piece->setPosition(finish);


}


void LudoBoard::moveFromHomeToBoard(int owner,int piecenb){

       int finish = ((52-(owner * 13))%52);
       LudoPiece* piece =this->c_getPlayer(owner)->getPiece(piecenb);
       this->setBoard(finish, piece);
       piece->setPosition(finish);

}

void LudoBoard::moveFromBoardToBoard(int piecenb,int owner, int finish){//bouge une piece du board au board toute conditions vérifiée

        LudoPiece* piece=this->c_getPlayer(owner)->getPiece(piecenb);

        this->setBoard(finish,piece);
        this->c_getBoardBox(finish)->setPosition(finish);
}




/*virtual void moveFromHomeToBoard(int owner,int piece);
virtual void moveFromBoardToBoard(int piece,int owner, int finish);
virtual void moveFromBridgeToBridge(int piece,int owner,int finish);
virtual void moveFromBoardToBridge(int start, int owner, int finish);*/




