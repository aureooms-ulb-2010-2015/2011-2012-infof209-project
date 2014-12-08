#ifndef CLICKABLEQLABEL_HPP
#define CLICKABLEQLABEL_HPP

#include <QMouseEvent>
#include <QLabel>
#include <iostream>

using namespace std;

class ClickableQLabel : public QLabel {

Q_OBJECT

private:
	int _diceNumber;
public:
	ClickableQLabel(int);
	void mousePressEvent(QMouseEvent*);
signals:
	void emitDiceNumber(int);
};

#endif
