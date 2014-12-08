#include "Ghost.hpp"
#include <QDebug>

Ghost::Ghost(int i, int j)
{
    this->_path="./Interface/Images/Ludo/shadow_horse.gif";
    _ghostMovie = new QMovie(this);
    _ghostMovie->setFileName(this->_path);
    this->setMovie(_ghostMovie);
    _ghostMovie->start();
    this->setCursor(Qt::CrossCursor);
    this->_gridi=i;
    this->_gridj=j;

}

int Ghost::getGridI(){return _gridi;}
int Ghost::getGridJ(){return _gridj;}
