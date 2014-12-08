#ifndef UICELL_HPP
#define UICELL_HPP
#include <QLabel>
#include <QString>


class UiCell : public QLabel
{

    private:
        int _structPosition;
        int _gridJ;
        int _gridI;
        QString _myColorPath;
        QString _horseState;



    public:
        UiCell();
        int getStructPosition();
        void setStructPosition(int);
        void setGridi(int);
        void setGridj(int);
        int getGridi();
        int getGridj();
        QString getMyColorPath();
        void setMycolorPath(QString);
        void colorMe();

        void init(int,int,int);
};

#endif // UICELL_HPP
