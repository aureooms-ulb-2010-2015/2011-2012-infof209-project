// Ludo
// Antoine de Wasseige - <Board.hpp>

#ifndef _BOARD_H_
#define _BOARD_H_

#include <vector>
#include <string>

#include "LudoPlayer.hpp"
#include "../../Board.hpp"

using namespace std;

class LudoBoard : public Board{


	
	protected:
		LudoPiece* _homeList[4][4];
		LudoPiece* _bridgeList[4][5];
		vector<GamePlayer*>* _listPlayers;
			
	public:
		// ----- _vectorHome -----
		LudoPiece** getPlayerHome(int PlayerID);
	
		// ----- _vectorBridge -----
		LudoPiece** getPlayerBridge(int PlayerID);
		LudoPiece* getPlayerBridgeBox(int PlayerID, int i);	
	
		// ----- _board -----
		LudoPiece*** getBoard();
		LudoPiece* c_getBoardBox(int i);
		virtual void setBoard(int, LudoPiece*);
		virtual void setHome(int,LudoPiece*);
		virtual void setBridge(int,LudoPiece*);
	
		// Constructeurs/Destructeurs
		LudoBoard();
		~LudoBoard();
		virtual void init(vector<GamePlayer*>*);
		LudoPlayer* c_getPlayer(int);
		virtual void eraseFromBoard(int);
		virtual void eraseFromHome(int owner, int piece);
		virtual void backInHome(int pos);
		virtual void moveFromHomeToBoard(int owner,int piece);
		virtual void moveFromBoardToBoard(int piece,int owner, int finish);
		virtual void moveFromBridgeToBridge(int piece,int owner,int finish);
		virtual void moveFromBoardToBridge(int piecenb,int owner, int finish);
		virtual void eraseFromBridge(int owner, int pos);

		virtual void display();
};
#endif
