#ifndef CHECKERSBOARD_HPP_INCLUDED
#define CHECKERSBOARD_HPP_INCLUDED

#include "CheckersPiece.hpp"
#include "../Board.hpp"



#include <string>

class CheckersBoard : public Board
{

  public:
    CheckersBoard();
    virtual ~CheckersBoard();

    virtual void addPiece(int,int,CheckersPiece*);
    virtual void removePiece(int,int);
    virtual CheckersPiece* getPiece(int,int);
    virtual void display();
    virtual void initBoard();
    virtual void checkForKings();
    virtual bool empty(int,int);
    virtual bool isInBoard(int,int);


};





#endif // CHECKERSBOARD_HPP_INCLUDED
