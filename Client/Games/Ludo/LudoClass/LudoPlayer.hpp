

#ifndef _PLAYER__H_
#define _PLAYER__H_

#include "../../GamePlayer.hpp"

#include <string>
#include <vector>
#include "LudoPiece.hpp"


class LudoPlayer: public GamePlayer{
	private:
		int _playerColor;
		int _idPlayer;
        protected:
		std::vector<LudoPiece*>* _hisPieces;
		
		
	public:
        LudoPlayer(std::string color, int id);
		~LudoPlayer();
		LudoPlayer(std::string);
		
		void showPiecesPosition();

		int makePosSum();
		
		void setplayerColor(int color);
		void setIDPlayer(int id);
		
		int getIDPlayer();
		int getPlayerColor();
		LudoPiece* getPiece(int i);
		std::vector<LudoPiece*>* getHisPieces();
};
#endif

