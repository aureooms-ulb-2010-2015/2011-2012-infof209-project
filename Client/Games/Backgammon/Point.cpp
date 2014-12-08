#include "Point.hpp"

Point::Point(QString colour){

	if(colour == "Red")
		this->setPixmap(QPixmap("./Interface/Images/Backgammon/Points/PointRouge.png"));
	else if (colour == "White")
		this->setPixmap(QPixmap("./Interface/Images/Backgammon/Points/PointBlanc.png"));
	else if (colour == "Red360")
		this->setPixmap(QPixmap("./Interface/Images/Backgammon/Points/PointRouge360.png"));
	else
		this->setPixmap(QPixmap("./Interface/Images/Backgammon/Points/PointBlanc360.png"));


}
