#include "CheckersGame.hpp"
#include "CheckersMove.hpp"

#include <cmath>
#include <string>
#include <sstream>
#include <stdlib.h>

using namespace std;


CheckersGame::CheckersGame(GameServer* server):Game(server,2,new CheckersBoard()){
	this->players()->push_back(new CheckersPlayer("White"));
	this->players()->push_back(new CheckersPlayer("Black"));



	this->_hasCapture = false;


}
CheckersGame::CheckersGame(GameServer* server,CheckersBoard* b):Game(server,2,b){
	this->players()->push_back(new CheckersPlayer("White"));
	this->players()->push_back(new CheckersPlayer("Black"));


	this->_hasCapture = false;
}

CheckersGame::~CheckersGame(){}

bool CheckersGame::validateMovement(int rowi,int columni,int rowf,int columnf,CheckersPlayer* player)
{

    if (this->c_board()->isInBoard(rowi,columni) && this->c_board()->isInBoard(rowf,columnf)
	&&  not (this->c_board()->empty(rowi,columni))
	&& (this->c_board()->getPiece(rowi,columni)->ownToPlayer(player))
	&& this->c_board()->empty(rowf,columnf)){
       	if (this->isCapturePossible(player)){
            this->_hasCapture = true;
            if (this->c_board()->getPiece(rowi,columni)->isAKing() && this->c_board()->getPiece(rowi,columni)->isValidMovement(rowi,columni,rowf,columnf)){
                int stepX = (columnf-columni < 0) ? -1 : 1;
                int stepY = (rowf-rowi < 0) ? -1 : 1;

                for(int pos = 0; columni + (stepX)*pos != columnf && rowi + (stepY)*pos != rowf; ++pos)
                {
                    if (not this->c_board()->empty(rowi+(stepY)*(pos+1),columni+(stepX)*(pos+1))
&& (this->c_board()->getPiece(rowi+(stepY)*(pos+1),columni+(stepX)*(pos+1))->getColour() != player->getColour()
&& (this->c_board()->empty(rowi+(stepY)*(pos+2),columni+(stepX)*(pos+2)))
&& columnf == columni+(stepX)*(pos+2) && rowf == rowi + (stepY)*(pos+2))){
                        return true;
                    }
                    else if (not this->c_board()->empty(rowi+(stepY)*(pos+1),columni+(stepX)*(pos+1)))
                        return false;
                }
                return false;
            }
            else
            {
                if((columnf-columni == -2 || columnf-columni == 2) && (rowf-rowi == -2 || rowf-rowi == 2) && not (this->c_board()->empty((rowi+rowf)/2,(columni+columnf)/2)) && this->c_board()->getPiece((rowi+rowf)/2,(columni+columnf)/2)->getColour() != player->getColour())
                {
                    return true;
                }
		return false;
            }
        }
        else
        {
            if (this->c_board()->getPiece(rowi,columni)->isAKing() && this->c_board()->getPiece(rowi,columni)->isValidMovement(rowi,columni,rowf,columnf))
            {
                int stepX = (columnf-columni < 0) ? -1 : 1;
                int stepY = (rowf-rowi < 0) ? -1 : 1;
                for(int pos = 1; columni + (stepX)*pos != columnf && rowi + (stepY)*pos != rowf; ++pos)
                {
                    if (not this->c_board()->empty(rowi+(stepY)*(pos+1),columni+(stepX)*(pos+1)))
                        return false;
                }
                return true;
            }
            else
            {
                if (fabs(columnf-columni) == 1)
                {
                    if(player->getColour() == "White" && rowf-rowi == -1)
                    {
                        return true;
                    }
                    else if(player->getColour() == "Black" && rowf-rowi == 1)
                    {
                        return true;
                    }
                }
                return false;
            }
        }
    }
    else
    {
        return false;
    }
}

void CheckersGame::makeMove(int rowi,int columni,int rowf,int columnf)
{
    
    
    
    if (this->c_board()->getPiece(rowi,columni)->isAKing()){
        int stepX = (columnf-columni < 0) ? -1 : 1;
        int stepY = (rowf-rowi < 0) ? -1 : 1;

        for(int pos = 0; columni + (stepX)*pos != columnf && rowi + (stepY)*pos != rowf; ++pos)
        {
            if (not this->c_board()->empty(rowi+(stepY)*(pos+1),columni+(stepX)*(pos+1))
            && (this->c_board()->getPiece(rowi+(stepY)*(pos+1),columni+(stepX)*(pos+1))->getColour() != this->c_board()->getPiece(rowi,columni)->getColour()
            && (this->c_board()->empty(rowi+(stepY)*(pos+2),columni+(stepX)*(pos+2)))
            && columnf == columni+(stepX)*(pos+2) && rowf == rowi + (stepY)*(pos+2)))
            {
                this->c_board()->removePiece(rowf - stepY,columnf - stepX);
            }
        }
    }
    else{
        if((columnf-columni == -2 || columnf-columni == 2) && (rowf-rowi == -2 || rowf-rowi == 2)
        && not (this->c_board()->empty((rowi+rowf)/2,(columni+columnf)/2))
        && this->c_board()->getPiece((rowi+rowf)/2,(columni+columnf)/2)->getColour() != this->c_board()->getPiece(rowi,columni)->getColour()){
            this->c_board()->removePiece((rowi+rowf)/2,(columni+columnf)/2);
        }
    }
	this->c_board()->addPiece(rowf,columnf,this->c_board()->getPiece(rowi,columni));
    this->c_board()->removePiece(rowi,columni);

}


bool CheckersGame::isCapturePossible(CheckersPlayer* player)
{
    for (int i = 0;i < 10; ++i)
    {
        for(int j = 0; j < 10; ++j)
        {
            if (this->c_board()->getPiece(i,j) != NULL && this->c_board()->getPiece(i,j)->getColour() == player->getColour())
            {
                if (this->c_board()->getPiece(i,j)->isAKing())
                {
                    //cout<<"King"<<endl;
                    if (this->capturePossibilityForKingPiece(i,j,this->c_board()->getPiece(i,j)))
                        return true;
                }
                else
                {
                    //cout<<"Not king"<<endl;
                    if (this->capturePossibilityForStandardPiece(i,j,this->c_board()->getPiece(i,j)))
                        return true;
                }
            }
        }
    }
    return false;
}



bool CheckersGame::capturePossibilityForKingPiece(int row,int column,CheckersPiece* aPiece)
{
    //cout<<"Checking diag"<<endl;
    for(int posUpR = 1; posUpR + column < 9 && row - posUpR > 0; ++posUpR)
    {
        if(not this->c_board()->empty(row-posUpR,column+posUpR))
        {
            if (this->c_board()->getPiece(row - posUpR,column + posUpR)->getColour() != aPiece->getColour() && this->c_board()->empty(row - posUpR - 1, column + posUpR + 1))
                return true;
			return false;
        }
    }
    for(int posUpL = 1; column - posUpL > 0 && row - posUpL > 0; ++posUpL )
    {

        if (not this->c_board()->empty(row - posUpL,column - posUpL ))
        {
            cout<<this->c_board()->getPiece(row-posUpL,column - posUpL)<<endl;
            if (this->c_board()->getPiece(row - posUpL,column - posUpL)->getColour() != aPiece->getColour() && this->c_board()->empty(row - posUpL - 1,column - posUpL - 1))
                return true;
			return false;
        }
    }
    for(int posDownR = 1; column + posDownR < 9 && row + posDownR < 9; ++posDownR )
    {
        if (not this->c_board()->empty(row + posDownR,column + posDownR))
        {
            //cout<<this->c_board()->getPiece(column + posDownR,row + posDownR)<<endl;
            if(this->c_board()->getPiece(row + posDownR,column + posDownR)->getColour() != aPiece->getColour() && this->c_board()->empty( row + posDownR + 1,column + posDownR + 1))
                return true;
			return false;
        }
    }
    for(int posDownL = 1; column - posDownL > 0 && row + posDownL < 9; ++posDownL )
    {
        if (not this->c_board()->empty(row + posDownL ,column - posDownL))
        {
            if (this->c_board()->getPiece(row + posDownL,column - posDownL)->getColour() != aPiece->getColour() && this->c_board()->empty(row + posDownL + 1,column - posDownL - 1))
                return true;
			return false;
        }
    }
	
	return false;
}

bool CheckersGame::capturePossibilityForStandardPiece(int row,int column,CheckersPiece* aPiece)
{
    bool upRight = (row > 1 && column < 8 && not this->c_board()->empty(row-1,column+1) && (aPiece->getColour() != (this->c_board()->getPiece(row-1,column+1)->getColour()) && this->c_board()->empty(row-2,column+2)));
    bool upLeft = (row > 1 && column > 1 && not this->c_board()->empty(row-1,column-1) && (aPiece->getColour() != (this->c_board()->getPiece(row-1,column-1)->getColour()) && this->c_board()->empty(row-2,column-2)));
    bool downRight = (row < 8 && column < 8 && not this->c_board()->empty(row+1,column+1) && (aPiece->getColour() != (this->c_board()->getPiece(row+1,column+1)->getColour()) && this->c_board()->empty(row+2,column+2)));
    bool downLeft = (row < 8 && column > 1 && not this->c_board()->empty(row+1,column-1) && (aPiece->getColour() != (this->c_board()->getPiece(row+1,column-1)->getColour()) && this->c_board()->empty(row+2,column-2)));
    if (upRight || upLeft || downRight || downLeft)
        return true;
    return false;
}

int CheckersGame::winner()
{

    string winnerCandidateColour = " ";
    for(int i = 0;i<10;++i)
    {
        for(int j=0; j<10;++j)
        {
            if(not (this->c_board()->getPiece(i,j) == NULL))
            {
                if(winnerCandidateColour != " " && (this->c_board()->getPiece(i,j))->getColour() != winnerCandidateColour )
                {
                    return -1;
                }
                winnerCandidateColour = (this->c_board()->getPiece(i,j))->getColour();
            }
        }
    }
    if (winnerCandidateColour == "White")
        return 0;
    if (winnerCandidateColour == "Black")
        return 1;
    return *new int;
}


bool CheckersGame::endOfGame(){
	return this->winner() != -1;
}

bool CheckersGame::endOfTurn(){
	return !(this->isCapturePossible(this->c_player()) && this->_hasCapture);
}

Move* CheckersGame::parseMove(string data){
	return new CheckersMove(data);
}

void CheckersGame::makeMove(Move* move){

	CheckersMove* cast = (CheckersMove*)(move);
	this->makeMove(cast->row_s(),cast->column_s(),cast->row_e(),cast->column_e());
	this->c_board()->checkForKings();

}

void CheckersGame::runActiveTurn(){
	int rowi,columni,rowf,columnf;
	do{
		do{
			this->displayTurn();
			cout<<"Entrer les coordonnées : "<<endl;
			if(this->isCapturePossible(this->c_player())){
				cout << "Vous devez capturer!" << endl;
			}
			cout<<"Entrez le numero de la ligne de depart :";
			cin>>rowi;
			cout<<"Entrez le numero de la colonne de depart : ";
			cin>>columni;
			cout<<"Entrez le numero de la ligne d'arrivee : ";
			cin>>rowf;
			cout<<"Entrez le numero de la colonne d'arrivee : ";
			cin>>columnf;
		}while(not validateMovement(rowi,columni,rowf,columnf,this->c_player()));

		CheckersMove* move = new CheckersMove(rowi,columni,rowf,columnf);
		this->handleMove(move);

		this->c_board()->checkForKings();
	}while (!this->endOfTurn());
	this->_hasCapture = false;
}

CheckersBoard* CheckersGame::c_board(){
    return (CheckersBoard*)(this->board());
}

CheckersPlayer* CheckersGame::c_player(){
    return (CheckersPlayer*)(this->player(this->id()));
}
