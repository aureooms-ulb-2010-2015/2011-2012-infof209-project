
#ifndef CHECKERSPIECE_HPP_INCLUDED
#define CHECKERSPIECE_HPP_INCLUDED


#include "CheckersPlayer.hpp"
#include "../Piece.hpp"
#include <string>
#include <iostream>

using namespace std;



class CheckersPiece : public Piece
{
  public:
    CheckersPiece(string);

    virtual ~CheckersPiece();

    virtual bool isAKing()=0;

    bool ownToPlayer(CheckersPlayer*);
	virtual bool isValidMovement(int,int,int,int);

    string getColour();

    virtual void display();
};

class StandardCheckersPiece : public CheckersPiece
{
  public:
    StandardCheckersPiece(string);
    ~StandardCheckersPiece();

    bool isAKing(){return false;}
    bool isValidMovement(int,int,int,int);
    void display();

};

class KingCheckersPiece : public CheckersPiece
{
  public:
    KingCheckersPiece(string);
    ~KingCheckersPiece();

    bool isAKing(){return true;}
    bool isValidMovement(int,int,int,int);
    void display();
};


#endif // CHECKERSPIECE_HPP_INCLUDED
