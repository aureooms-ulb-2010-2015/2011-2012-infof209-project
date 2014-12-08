#include "CheckersBoard.hpp"
#include <string>
#include <iostream>

using namespace std;

CheckersBoard::CheckersBoard():Board(10,10)
{
    this->initBoard();

}
CheckersBoard::~CheckersBoard()
{

}

void CheckersBoard::addPiece(int row,int column, CheckersPiece* piece)
{
    this->_board[row][column] = piece;
}

void CheckersBoard::removePiece(int row,int column)
{
    this->_board[row][column] = NULL;
}

bool CheckersBoard::empty(int row,int column)
{
    if (this->_board[row][column] == NULL)
    {
        //cout<<"Empty case"<<endl;
        return true;
    }

    //cout<<"not Empty case !"<<endl;
    return false;
}

bool CheckersBoard::isInBoard(int row,int column)
{
    if ((row >= 0 && row < 10) && (column >= 0 && column < 10))
    {
        cout<<"Is in board"<<endl;
        return true;
    }

    cout<<"Not in board"<<endl;
    return false;
}

void CheckersBoard::display()
{
    //Fonction d'affichage du plateau
    cout<<"   0 1 2 3 4 5 6 7 8 9"<<endl;
    for (int i = 0;i<10;++i)
    {
        cout<<"\n   ------------------- "<<endl<<i<<" ";
        cout<<"|";
        for(int j = 0;j<10;++j)
        {
            if (this->_board[i][j] != NULL)
                (this->_board[i][j])->display(); //Appel de la fonction display() de pièce.
            else
                cout<<" |";
        }
    }
    cout<<"\n  -------------------- "<<endl;
    cout<<"\n\n";
}

void CheckersBoard::initBoard()
{
    for (int i = 0;i<10;++i)
    {
        for(int j = 0;j<10;++j)
        {
            //Placement des pieces sur le plateau de jeu
            if(i<4 && i%2 != j%2)
                _board[i][j] = new StandardCheckersPiece("Black");
            else if (i>5 && i%2 != j%2)
                _board[i][j] = new StandardCheckersPiece("White");
            else
                _board[i][j] = NULL;
                /*_board[4][5] = new KingCheckersPiece("White");
                _board[6][7] = new KingCheckersPiece("Black");
                _board[0][0] = new KingCheckersPiece("White");
                _board[0][1] = new KingCheckersPiece("Black");*/
        }
    }

}

CheckersPiece* CheckersBoard::getPiece(int row,int column)
{
    return (CheckersPiece*)this->_board[row][column];
    //return this->getPieceInCell(row,column);
}


void CheckersBoard::checkForKings()
{
    for(int i = 0; i < 10;++i)
    {
        if (this->_board[0][i] != NULL && this->_board[0][i]->getColour() == "White")
        {
            this->_board[0][i] = new KingCheckersPiece("White");
        }
        else if (this->_board[9][i] != NULL && this->_board[9][i]->getColour() == "Black")
        {
            this->_board[9][i] = new KingCheckersPiece("Black");
        }
    }
}
