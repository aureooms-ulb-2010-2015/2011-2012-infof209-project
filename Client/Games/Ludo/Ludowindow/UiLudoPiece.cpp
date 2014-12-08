#include "UiLudoPiece.hpp"
#include "UiLudoCell.hpp"
#include <QDebug>


UiLudoPiece::UiLudoPiece(QString owner,int position , int number) :LudoPiece( owner.toStdString(), number)
{
    int intowner = owner.toInt();
   _informationDesk=new InformationDesk;
   _path=_informationDesk->getHorsePath(intowner);
   _clickCount=0;
   _horseMovie = new QMovie(this);
   _horseMovie->setFileName(_path);
   this->_clickEnabled=false;
   this->setPosition(position);

   
	this->run();
	this->stop();



}
int UiLudoPiece::getClickCount(){
	return this->_clickCount;


}

void UiLudoPiece::run(){
    this->setMovie(_horseMovie);
    this->_clickEnabled=true;
    _horseMovie->start();

    this->setCursor(Qt::PointingHandCursor);


}
void UiLudoPiece::stop(){

    _horseMovie->stop();
    this->_clickEnabled=false;
    this->setCursor(Qt::ForbiddenCursor);

}





void UiLudoPiece::resetClickCount(){
    this->_clickCount=0;
}

void UiLudoPiece::mousePressEvent ( QMouseEvent * event ){
    if( this->_clickEnabled){
        this->_clickCount++;
        if(this->_clickCount==1){
            emit IWantMyGhostToBeShown(this->getNumber());
        }
        else if (this->_clickCount==2){
            emit this->clicked(this->getPosition(),this->getNumber());
        }
    }
}

UiLudoPiece::~UiLudoPiece(){delete(_horseMovie);}






void UiLudoPiece::setGhost(Ghost* ghost){_ghost = ghost;}
Ghost* UiLudoPiece::getGhost(){return _ghost;}











