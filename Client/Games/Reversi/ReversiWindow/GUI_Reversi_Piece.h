#ifndef GUI_REVERSI_PIECE_H
#define GUI_REVERSI_PIECE_H

#include <QLabel>
#include <QObject>

#include "../h/ReversiPiece.h"
class GUI_Reversi_Piece : public QLabel, public ReversiPiece{
private:
	static QString BLACK;
	static QString WHITE;
	QString __img_file;

public:
	GUI_Reversi_Piece();
	GUI_Reversi_Piece(QWidget* parent);
	virtual ReversiPiece& setBlack();
	virtual ReversiPiece& setWhite();
	virtual ReversiPiece& unset();
	GUI_Reversi_Piece& refresh();
};

#endif // GUI_REVERSI_PIECE_H
