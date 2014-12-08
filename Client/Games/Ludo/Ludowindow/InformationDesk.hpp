#ifndef INFORMATIONDESK_HPP
#define INFORMATIONDESK_HPP

#include <QString>

class InformationDesk
{

    private:
        QString _bluePath;
        QString _yellowPath;
        QString _redPath;
        QString _greenPath;
        QString _greyPath;
        QString _voidPath;



        QString _horsesPaths[5];
    public:
        InformationDesk();
        bool northSide(int,int);
        bool eastSide(int,int);
        bool westSide(int,int);
        bool southSide(int,int);

        bool isGreenHome(int,int);
        bool isBlueHome(int,int);
        bool isYellowHome(int,int);
        bool isRedHome(int,int);

        QString getBluePath();
        QString getYellowPath();
        QString getRedPath();
        QString getGreenPath();
        QString getGreyPath();
        QString getVoidPath();

        QString getHorsePath(int);


};

#endif // INFORMATIONDESK_HPP
