#include "GUI_Reversi_Box.h"
GUI_Reversi_Box::GUI_Reversi_Box(int column,int row):_clickEnabled(false){
	this->_column = column;
	this->_row = row;
	this->_piece = NULL;
	this->setFixedSize(55,55);
	this->setStyleSheet("QWidget { background-color: #16690F; }");
}


void GUI_Reversi_Box::clickable(){
	this->setCursor(Qt::PointingHandCursor);
	this->_clickEnabled = true;
	this->setStyleSheet("QWidget { background-color: #55AB48; }");
}


void GUI_Reversi_Box::notClickable(){
	this->setCursor(Qt::ArrowCursor);
	this->_clickEnabled = false;
	this->setStyleSheet("QWidget { background-color: #16690F; }");
}

void GUI_Reversi_Box::mousePressEvent(QMouseEvent *event){
	if (this->_clickEnabled){	
		emit this->clicked(this->_column,this->_row);
	}
}


void GUI_Reversi_Box::paintEvent(QPaintEvent * event){
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
