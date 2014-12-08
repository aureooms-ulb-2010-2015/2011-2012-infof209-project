#ifndef GUICHECKERSBOARD_HPP_INCLUDED
#define GUICHECKERSBOARD_HPP_INCLUDED

#include "CheckersBoard.hpp"

#include <QGridLayout>
#include <QLabel>
#include <QPixmap>

class GuiCheckersBoard : public CheckersBoard,public QGridLayout
{
  protected:
    QLabel* labelGrid[10][10];
  public:
    GuiCheckersBoard();
    ~GuiCheckersBoard();
    virtual void addPiece(int,int,CheckersPiece*);
    virtual void removePiece(int,int);
    virtual void selectPiece(int,int);
    virtual void unselectPiece(int,int);
    virtual void initBoard();
    virtual void checkForKings();

};

#endif // GUICHECKERSBOARD_HPP_INCLUDED
