#include "UiCell.hpp"

UiCell::UiCell()
{
}
void UiCell::setGridi(int i){_gridI=i;}
void UiCell::setGridj(int j){_gridJ=j;}
int UiCell::getGridi(){return _gridI;}
int UiCell::getGridj(){return _gridJ;}
QString UiCell::getMyColorPath(){return _myColorPath;}
void UiCell::setMycolorPath(QString colorPath){_myColorPath=colorPath;}
int UiCell::getStructPosition(){return _structPosition;}
void UiCell::setStructPosition(int pos){_structPosition=pos;}
void UiCell::colorMe(){this->setPixmap(QPixmap(getMyColorPath()));}
void UiCell::init(int i, int j, int k){


    this->colorMe();
    this->setStructPosition(k);
    this->setGridi(i);
    this->setGridj(j);
}

