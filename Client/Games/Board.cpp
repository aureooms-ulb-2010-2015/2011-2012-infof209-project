
#include "Board.hpp"

Board::Board(int x,int y){

	_board = new Piece** [x];
	for (int i = 0;i<x;++i){
		
		_board[i] = new Piece* [y];
		for(int j =0;j<y;++j)
			_board[i][j] = NULL;
			
	}
	

}

Board::~Board(){


}

Piece* Board::getPieceInCell(int x){
	return _board[x][0];
	
}

Piece* Board::getPieceInCell(int x,int y){
	return _board[x][y];
}

void Board::addPiece(int x, Piece* piece){
	_board[x][0] = piece;
	
}

void Board::addPiece(int x,int y,Piece* piece){
	_board[x][y] = piece;

}

void Board::removePiece(int x){
	_board[x][0] = NULL;
	
}

void Board::removePiece(int x,int y){
	
	_board[x][y] = NULL;
	
}

bool Board::isEmpty(int x,int y){
	return _board[x][y] == NULL;
}
