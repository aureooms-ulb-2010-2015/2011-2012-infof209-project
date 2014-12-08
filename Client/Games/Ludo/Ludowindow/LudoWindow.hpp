#ifndef LUDOFEN_HPP
#define LUDOFEN_HPP


#include "UiLudoCell.hpp"
#include "UiOwnedCell.hpp"
#include "UiVoidCell.hpp"
#include "UiLudoBoard.hpp"
#include "../LudoClass/Ludo.hpp"
#include "UiLudoPlayer.hpp"
#include "UiLudoPiece.hpp"
#include "InformationDesk.hpp"
#include "Ghost.hpp"
#include <QApplication>
#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QString>



class LudoWindow : public QWidget,  public Ludo
{
    Q_OBJECT
    private:
        UiLudoBoard* _uiBoard;
    signals:
    	void runActiveTurn_signal();

    public slots:
        virtual void horseClicked(int start, int piece);
        virtual void ghostRequest(int piece);
        virtual void runActiveTurn_slot();


    public:
        LudoWindow(int, GameServer*);
        virtual void DisplayPlayablePieces();
        virtual void runActiveTurn();
        virtual void endActiveTurn();
        virtual UiLudoBoard* c_getMainBoard();
       	virtual bool YouCanPlay();
		





};


/*

layout->removeWidget(widget);
delete widget;
*/

#endif // LUDOFEN_HPP
