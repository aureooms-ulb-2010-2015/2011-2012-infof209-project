#ifndef GUI_REVERSI_BOARD_GRID_H
#define GUI_REVERSI_BOARD_GRID_H
#include <QGridLayout>
#include <QObject>

#include "../h/ReversiBoard.h"
#include "GUI_Reversi_Box.h"

class GUI_Reversi_Board_Grid: public QGridLayout, public ReversiBoard{
public:
	GUI_Reversi_Box* _grid[8][8];
	GUI_Reversi_Board_Grid();
	
	void addPiece(int,int,Piece*);
};

#endif // GUI_REVERSI_BOARD_GRID_H
