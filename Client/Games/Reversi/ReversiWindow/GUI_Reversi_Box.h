#ifndef GUI_REVERSI_BOX_H
#define GUI_REVERSI_BOX_H

#include <QWidget>
#include <QObject>
#include <QStyle>
#include <QStyleOption>
#include <QPainter>

#include "GUI_Reversi_Piece.h"
class GUI_Reversi_Box : public QWidget{
    Q_OBJECT

public:

	int _row;
	int _column;
	GUI_Reversi_Piece* _piece;
	bool _clickEnabled;

	GUI_Reversi_Box(int,int);
	void clickable();
	void notClickable();
	void paintEvent(QPaintEvent*);
protected:
	void mousePressEvent(QMouseEvent* event);

signals:
	void clicked(unsigned short int,unsigned short int);
};

#endif // GUI_REVERSI_BOX_H
