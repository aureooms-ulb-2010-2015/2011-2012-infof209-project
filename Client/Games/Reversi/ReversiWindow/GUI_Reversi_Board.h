#ifndef GUI_REVERSI_BOARD_H
#define GUI_REVERSI_BOARD_H


#include <QWidget>
#include <QObject>
#include <QStyle>
#include <QStyleOption>
#include <QPainter>

#include "../h/Reversi.h"

class GUI_Reversi_Board : public QWidget, public Reversi{
	Q_OBJECT
private:
	//Reversi* _game;

public:
	GUI_Reversi_Board(GameServer* server);
	//Game* game(){return this->_game;}
	//void displayTurn(){}
	//void displayEndOfGame(){}
	void runActiveTurn();
	void endActiveTurn();
	void paintEvent(QPaintEvent*);
	
	
	virtual void refresh(Request*);
	virtual void refresh(string);
	
	
public slots:
	void click_at(unsigned short int,unsigned short int);
	void data_received_slot(QString);
	void emph_clickable_slot();
	void end_active_turn_slot();
	
signals:
	void data_received_signal(QString);
	void emph_clickable_signal();
	void end_active_turn_signal();
};


#endif // GUI_REVERSI_BOARD_H
