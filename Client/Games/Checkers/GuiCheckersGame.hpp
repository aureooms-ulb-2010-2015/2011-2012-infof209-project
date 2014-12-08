#ifndef GUICHECKERSGAME_HPP_INCLUDED
#define GUICHECKERSGAME_HPP_INCLUDED

#include "CheckersGame.hpp"
#include "GuiCheckersBoard.hpp"
#include "CheckersMove.hpp"
#include <QWidget>
#include <QVBoxLayout>
#include <QMouseEvent>
#include <QMessageBox>
#include <QLabel>
#include <QString>
#include <QObject>

class GuiCheckersGame : public QWidget, public CheckersGame{
	Q_OBJECT
protected:
	
	QVBoxLayout* _principalLayout;
	QLabel* _controlPanel;
	int firstXmove;
	int firstYmove;
	int secondXmove;
	int secondYmove;
	bool isClickEnable;
	
protected:
	void mousePressEvent(QMouseEvent * ev);
	
public slots:
	void data_received_slot(QString);
	
signals:
	void data_received_signal(QString);
	
public:

	GuiCheckersGame(GameServer*);
	virtual ~GuiCheckersGame();
	virtual GuiCheckersBoard* c_board();
	virtual void runActiveTurn();
	virtual void endActiveTurn();
	
	
	virtual void refresh(Request*);
	virtual void refresh(string);

};


#endif // GUICHECKERSGAME_HPP_INCLUDED
