#include <iostream>
#include "GUI_Reversi_Piece.h"
#include <QtGlobal>
#include <QPainter>
#include <QResizeEvent>
#include <QCoreApplication>

QString GUI_Reversi_Piece::BLACK = "./Interface/Images/Reversi/black.png";
QString GUI_Reversi_Piece::WHITE = "./Interface/Images/Reversi/white.png";

GUI_Reversi_Piece::GUI_Reversi_Piece(){

    this->setGeometry(0,0,55,55);
}

GUI_Reversi_Piece::GUI_Reversi_Piece(QWidget* parent) : QLabel(parent){

    this->setGeometry(0,0,55,55);

}

ReversiPiece& GUI_Reversi_Piece::setBlack(){
	this->__img_file = GUI_Reversi_Piece::BLACK;
	this->refresh();
	return ReversiPiece::setBlack();
}

ReversiPiece& GUI_Reversi_Piece::setWhite(){
	this->__img_file = GUI_Reversi_Piece::WHITE;
	this->refresh();
	return ReversiPiece::setWhite();
}

ReversiPiece& GUI_Reversi_Piece::unset(){
	this->__img_file = "";
	this->refresh();
	return ReversiPiece::unset();
}

GUI_Reversi_Piece& GUI_Reversi_Piece::refresh(){
	QPixmap pixmap(this->__img_file);
	this->setPixmap(pixmap);
	return *this;
}
