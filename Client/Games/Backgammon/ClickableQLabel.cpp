
#include "ClickableQLabel.hpp"

ClickableQLabel::ClickableQLabel(int diceNumber) : QLabel(){
	_diceNumber = diceNumber;
}

void ClickableQLabel::mousePressEvent(QMouseEvent* event){
	if(event->button() == Qt::LeftButton)
		emit emitDiceNumber(_diceNumber);
}
