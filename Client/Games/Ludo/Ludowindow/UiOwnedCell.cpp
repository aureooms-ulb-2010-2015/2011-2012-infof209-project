#include "UiOwnedCell.hpp"


UiOwnedCell::UiOwnedCell(){}
UiOwnedCell::UiOwnedCell(QString path,int owner){

    this->setMycolorPath(path);
    this->colorMe();
    this->setOwnerId(owner);
    this->setCaseNumber(-1);

}
int UiOwnedCell::getOwnerId(){return _ownerId;}
void UiOwnedCell::setOwnerId(int id){_ownerId=id;};
