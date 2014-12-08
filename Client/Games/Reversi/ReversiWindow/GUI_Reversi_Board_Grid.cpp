
#include "GUI_Reversi_Board_Grid.h"
#include "GUI_Reversi_Piece.h"

GUI_Reversi_Board_Grid::GUI_Reversi_Board_Grid(){


    for(unsigned short int row = 0; row<8 ; row++){
        for(unsigned short int column = 0; column<8; column++){
            GUI_Reversi_Box* reversiBoardBox = new GUI_Reversi_Box(column,row);
            this->addWidget(reversiBoardBox,row,column);
	    	this->_grid[column][row] = reversiBoardBox;
        }
    }
    
    

}


void GUI_Reversi_Board_Grid::addPiece(int row,int column,Piece* piece){

	ReversiBoard::addPiece(row,column,piece);
	this->_grid[column][row]->_piece = (GUI_Reversi_Piece*)piece;
	((GUI_Reversi_Piece*)piece)->setParent(this->_grid[column][row]);
	((GUI_Reversi_Piece*)piece)->show();
}

