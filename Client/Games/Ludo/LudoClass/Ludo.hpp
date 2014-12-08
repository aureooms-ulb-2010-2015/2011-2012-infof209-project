// Ludo
// Chaste Gauvain - 2011/12 - <Ludo.hpp>

#ifndef _LUDO_H_
#define _LUDO_H_

#include "../../DiceGame.hpp"

#include "LudoBoard.hpp"

#include "../../../../Init/Init.hpp"
#include "../../../../Common/Request.hpp"
#include "../../../GameServer.hpp"

#include <vector>

#include "LudoMove.hpp"

using namespace std;

class Ludo : public DiceGame{


    protected:
        bool _isPlayablePieces[3];

    public:
	
		// Constructeur/Destructeur
		Ludo(int nbplayer,GameServer* server );
		Ludo(int nbplayers ,GameServer* server, LudoBoard* board);
		virtual ~Ludo();
		virtual void resetPlayablePieces();
	
		// Méthodes pour jouer
		//virtual void testPossibleMove(int PlayerID, bool* isPlayablePieces, int Dice);
	
        virtual bool YouCanPlay();
		//virtual void MovePiece(int PlayerID, int PieceNumber, int Dice);

        virtual void move(int start, int finish, int piece, int owner);
	
	
			
		//virtual int chooseFirstPlayer();
	
		//bool freeWayTest(int CurrentPlayerID, int piecenumber ,int Dice );
	
	
		// Méthodes d'affichage
        virtual void DisplayPlayablePieces();
		virtual void checkdata();
	
		virtual void showIt();
		virtual const char* g(int pos, int PlayerID, int place);
		virtual int printval(int pos, int PlayerID, int place);
	
        //GETTERS SETTERS
	
		virtual LudoPlayer* getPlayer(int i);
		virtual LudoBoard* c_getMainBoard();
        virtual int getChosenPiece();
	
		virtual void displayBoard();


		virtual int winner();
		virtual bool endOfGame();
		virtual Move* parseMove(string);
		virtual void makeMove(Move*);
		virtual void runActiveTurn();
		virtual bool endOfTurn();
	
		virtual bool playable(LudoPiece*);
		virtual bool isInHome(LudoPiece*);
		virtual bool startPointIsOk();
		virtual bool arrivalPointIsOk(LudoPiece*);

		virtual bool myBridgePosIsFree(int);
		virtual bool boardPosIsFree(int);
		virtual bool noPieceOnBoard(int);


		
};
#endif
