#ifndef UILUDOBOARD_HPP
#define UILUDOBOARD_HPP
#include"LudoBoard.hpp"
#include "UiCell.hpp"
#include "UiLudoCell.hpp"
#include "UiOwnedCell.hpp"
#include "UiVoidCell.hpp"
#include "UiLudoPiece.hpp"
#include "UiLudoPlayer.hpp"
#include "Ghost.hpp"
#include <QGridLayout>


class UiLudoBoard : public QGridLayout, public LudoBoard
{
    protected:
        InformationDesk* _informationDesk;

        UiLudoCell* _cells[52];
        UiOwnedCell * _homes[15];
        UiOwnedCell * _bridges[19];
        UiVoidCell * _void[153];//(15*15)-(6*3) une aile *4 car il en a quatre=225-72=153
        UiLudoPiece* _horses[15];
        int _nbPlayers;


    public:
        UiLudoBoard(int);
        void letsPutSomeColor();
        void putHorse(QLabel*, UiLudoCell*);

        void showIt();

        virtual void makeItRun(int,int);
        virtual void stopIt(int,int);
        virtual void stopThem();

        virtual UiLudoCell* getCell(int);
        virtual UiOwnedCell* getBridgeCell(int ,int);
        virtual UiOwnedCell* getHomeCell(int,int);
        virtual void setBoard (int,LudoPiece *);
        virtual void setHome (int,LudoPiece *);
        virtual void setBridge (int,LudoPiece *);

        virtual void init(vector<GamePlayer*>*);
        virtual UiLudoPiece* c_getPieceInCell(int pos);
        virtual UiLudoPiece* c_getPlayerBridgeBox(int PlayerID, int i);
        virtual UiLudoPiece* findHorse(int owner,int piece);
        virtual UiLudoPiece* getHorse(int);
        virtual Ghost* displayMyGhost(int, int,int );
        virtual UiLudoPiece** getHorses();
        virtual void moveHorse(UiLudoPiece* horse, UiLudoCell* cell);
        virtual  LudoPlayer* c_getPlayer(int);
        virtual void backInHome(int piece, int owner);
		virtual void ghostBuster();

        virtual UiLudoPiece* c_getBoardBox(int);
        void showCells();
        virtual void makeSum();






};

#endif // UILUDOBOARD_HPP
