#ifndef BACKGAMMONUI_HPP
#define BACKGAMMONUI_HPP

#include <QWidget>
#include <QPalette>
#include <QBrush>
#include <QImage>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QString>
#include <QSpacerItem>
#include <QMouseEvent>
//#include <iostream>
#include "Point.hpp"
#include "ClickableQLabel.hpp"

#include "Backgammon.hpp"

//using namespace std;

class BackgammonUI : public QWidget, public Backgammon {

Q_OBJECT

public:
	BackgammonUI(GameServer*);
	void createPieces();
	void createBoard();
	void putPiecesOnBoard();
	void setDice(int,int,int,int);
	

private:
	int selectedDice;
	QHBoxLayout* dice;
	QGridLayout* board;
	QVBoxLayout* display;

	ClickableQLabel* dice1;
	ClickableQLabel* dice2;
	ClickableQLabel* dice3;
	ClickableQLabel* dice4;

	QLabel* backgammonPieces[30];
	QVBoxLayout* points[24];
	QGridLayout* pawns[24];

public slots:
	void setSelectedDice(int);
};

#endif
