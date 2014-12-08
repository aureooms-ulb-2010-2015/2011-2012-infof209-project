#include "InformationDesk.hpp"

InformationDesk::InformationDesk()
{
    _bluePath="./Interface/Images/Ludo/blue_case.png";
    _yellowPath=  "./Interface/Images/Ludo/yellow_case.png";
    _redPath=  "./Interface/Images/Ludo/red_case.png";
    _greenPath= "./Interface/Images/Ludo/green_case.png";
    _greyPath=  "./Interface/Images/Ludo/grey_case.png";
    _voidPath=  "./Interface/Images/Ludo/void_case.png";

    _horsesPaths[0]="./Interface/Images/Ludo/red_horse.gif";
    _horsesPaths[1]="./Interface/Images/Ludo/green_horse.gif";
    _horsesPaths[2]="./Interface/Images/Ludo/yellow_horse.gif";
    _horsesPaths[3]="./Interface/Images/Ludo/blue_horse.gif";
    _horsesPaths[4]="./Interface/Images/Ludo/shadow_horse.gif";


}

bool InformationDesk::northSide(int i,int j){ return ( ( (0<=i)&&(i<=5) ) && ( (6<=j)&&(j<=8) )  );}
bool InformationDesk::eastSide(int i,int j){return (  ((6<=i)&&(i<=8))  && (j>=9)      );}
bool InformationDesk::westSide(int i,int j){return ( ((6<=i)&&(i<=8))  && (j<=5) );}
bool InformationDesk::southSide(int i,int j){return (  (9<=i)  && ( (j>=6) && (j<=8) )    ) ;}


QString InformationDesk::getBluePath(){return _bluePath;}
QString InformationDesk::getYellowPath(){return _yellowPath;}
QString InformationDesk::getRedPath(){return _redPath;}
QString InformationDesk::getGreenPath(){return _greenPath;}
QString InformationDesk::getGreyPath(){return _greyPath;}
QString InformationDesk::getVoidPath(){return _voidPath;}

QString InformationDesk::getHorsePath(int owner){return _horsesPaths[owner];}

bool InformationDesk::isGreenHome(int i,int j){

    bool isLowerLeftCorner=( (i==1)&&(j==0) );

    bool isUpperLeftCorner=( (i==0)&&(j==0) );

    bool isLowerRightCorner=( (i==1)&&(j==1) );

    bool isUpperRightCorner=( (i==0)&&(j==1) );




    return isLowerLeftCorner or isUpperLeftCorner or isLowerRightCorner or isUpperRightCorner;


}


bool InformationDesk::isRedHome(int i,int j){

    bool isLowerLeftCorner=( (i==1)&&(j==13) );

    bool isUpperLeftCorner=( (i==0)&&(j==13) );

    bool isLowerRightCorner=( (i==1)&&(j==14) );

    bool isUpperRightCorner=( (i==0)&&(j==14) );




    return isLowerLeftCorner or isUpperLeftCorner or isLowerRightCorner or isUpperRightCorner;


}

bool InformationDesk::isYellowHome(int i,int j){

    bool isLowerLeftCorner=( (i==14)&&(j==0) );

    bool isUpperLeftCorner=( (i==13)&&(j==0) );

    bool isLowerRightCorner=( (i==14)&&(j==1) );

    bool isUpperRightCorner=( (i==13)&&(j==1) );




    return isLowerLeftCorner or isUpperLeftCorner or isLowerRightCorner or isUpperRightCorner;


}

bool InformationDesk::isBlueHome(int i,int j){

    bool isLowerLeftCorner=( (i==14)&&(j==13) );

    bool isUpperLeftCorner=( (i==13)&&(j==13) );

    bool isLowerRightCorner=( (i==14)&&(j==14) );

    bool isUpperRightCorner=( (i==13)&&(j==14) );

    return isLowerLeftCorner or isUpperLeftCorner or isLowerRightCorner or isUpperRightCorner;


}

