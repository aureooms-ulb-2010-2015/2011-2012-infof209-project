#ifndef HORSE_HPP
#define HORSE_HPP

#include <QLabel>
#include <QString>
#include <QMovie>
#include <QCursor>
#include <QDebug>
#include "InformationDesk.hpp"
#include "../LudoClass/LudoPiece.hpp"
#include "Ghost.hpp"


class UiLudoPiece  : public QLabel, public LudoPiece
{
    Q_OBJECT


    signals:
        void clicked(int,int);
        void IWantMyGhostToBeShown(int);


    private:
        InformationDesk* _informationDesk;
        QString _path;
        QMovie *_horseMovie;
        Ghost * _ghost;
        bool _clickEnabled;
        int _clickCount;


    public:
        UiLudoPiece(QString,int,int);
        virtual ~UiLudoPiece();
        virtual void run();
        virtual void stop();
        virtual void resetClickCount();
        virtual Ghost* getGhost();
        virtual void setGhost(Ghost*);
        virtual int getClickCount();


    protected:
        void mousePressEvent ( QMouseEvent * event );
};

#endif // HORSE_HPP
