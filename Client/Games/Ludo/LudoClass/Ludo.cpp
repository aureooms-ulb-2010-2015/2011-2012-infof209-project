#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>

#include "Ludo.hpp"


using namespace std;

// ======================== Constructeurs & Destructeurs ========================

Ludo::Ludo(int nbplayers ,GameServer* server) : DiceGame(server, nbplayers ,new LudoBoard()) {
	
	

	for (int i = 0 ; i<this->getRequiredPlayers() ; i++){
		ostringstream temp;
		temp << i;

        LudoPlayer* newPlayer = new LudoPlayer(temp.str(),i);
		this->players()->push_back(newPlayer);
	}

	
	this->c_getMainBoard()->init(this->players());

}

Ludo::Ludo(int nbplayers ,GameServer* server, LudoBoard* board): DiceGame(server, nbplayers,board){}


Ludo::~Ludo(){
	int i=0;
	while (i<this->getRequiredPlayers()){
		delete(this->player(i));
		i++;
	}
}

// ======================== Méthodes du jeu ========================


void Ludo::resetPlayablePieces(){

    for (int i = 0; i < 4; i++){
    this->_isPlayablePieces[i] = false;

    }


}





bool Ludo::YouCanPlay(){
	
	bool YouCanPlay = false;
	
	string joueur;
	if(this->id()==0){joueur="\033[31mPlayer One\033[0;0m";}
	else if(this->id()==1){joueur="\033[32mplayer Four\033[0;0m";}
	else if(this->id()==2){joueur="\033[33mplayer Three\033[0;0m";}
	else if(this->id()==3){joueur="\033[34mplayer Two\033[0;0m";}
	
        if (this->_isPlayablePieces[0] || this->_isPlayablePieces[1] || this->_isPlayablePieces[2] || this->_isPlayablePieces[3]){
		cout << joueur << ", the value of your dice : " << this->getDice() <<endl;
		cout << "choose a pawn among these : ";
                DisplayPlayablePieces();
		YouCanPlay = true;
	}
	else{
		cout << "sorry " << joueur <<", the value of the dice is " << this->getDice() << " and you have no playable pawn with this dice." << endl;
	}
	return YouCanPlay;
}	

// ---------- Affiche la liste des pions jouables ----------
void Ludo::DisplayPlayablePieces(){
	
	for (int i = 0; i < 4; i++){
                if (this->_isPlayablePieces[i] == true){
			cout << " " << i + 1;
		}
	}
	cout << endl;
}



void Ludo::move(int start, int finish, int piece, int owner){
	
	

	int jumpOnBridge = ((52-(owner*13))-2);
	

	if (start>=jumpOnBridge){
	
		if (start>=100){//(	bridge bridge)
		

            this->c_getMainBoard()->eraseFromBridge(owner, start-100);
            this->c_getMainBoard()->moveFromBridgeToBridge(piece, owner, finish);//bouge la piecede start à finish (sur le bridge)
		
		
		
		}
	
		else if (start==jumpOnBridge){//(board bridge)
		

        	this->c_getMainBoard()->eraseFromBoard(start);
        	this->c_getMainBoard()->moveFromBoardToBridge(piece, owner , finish);
		}
	
		else{//board board
		
			finish=finish%52;
			if (!this->noPieceOnBoard(finish)){//si il y a une piece en position d'arrivée sur le board

				this->c_getMainBoard()->backInHome(finish);//on mets la piece adverse dans sa home		
				this->c_getMainBoard()->eraseFromBoard(finish);


			}


			this->c_getMainBoard()->eraseFromBoard(start);
			this->c_getMainBoard()->moveFromBoardToBoard(piece,owner,finish);//bouge la piecede de start à finish (sur le board)
	
		}
	
	}
	
	else{
	
		if (start==-1){//home board

			if (!this->noPieceOnBoard(finish)){//si il y a une piece en position d'arrivée sur le board

				this->c_getMainBoard()->backInHome(finish);//on mets la piece adverse dans sa home
				this->c_getMainBoard()->eraseFromBoard(finish);


			}
			
        	this->c_getMainBoard()->eraseFromHome(owner, piece);//efface la Piece du home
        	this->c_getMainBoard()->moveFromHomeToBoard(owner, piece);//bouge la piecede de home à startingpoint (sur le board)
		
		}
		
		else if (finish>jumpOnBridge){//(board bridge)

        	this->c_getMainBoard()->eraseFromBoard(start);
        	this->c_getMainBoard()->moveFromBoardToBridge(piece, owner , finish);
		
		}
		
		else{  //board board
			finish=finish%52;
			if (!this->noPieceOnBoard(finish)){//si il y a une piece en position d'arrivée sur le board

				this->c_getMainBoard()->backInHome(finish);//on mets la piece adverse dans sa home
				this->c_getMainBoard()->eraseFromBoard(finish);
				

			}
	

			this->c_getMainBoard()->eraseFromBoard(start);
			this->c_getMainBoard()->moveFromBoardToBoard(piece,owner,finish);//bouge la piecede de start à finish (sur le board)
		
		
		}
	
	}
	
	

}




// ---------- Vérifie si il y a un gagnant ----------
int Ludo::winner(){
	
	int res=-1;
	bool found = false;
	for(int i = 0; (i < this->getRequiredPlayers()) && (!found); ++i){
		if (this->getPlayer(i)->makePosSum()==410){	//un joueur qui gagne a ses pions en position 101,102,103,104 la somme des position vaut 410
			found=true;
		}	//c'est le seul cas ou une somme de position peut valoir 410
		if (found){
			res=i-1;
		}
	}
	return res;
}

// ======================== Setters & Getters ========================


LudoPlayer* Ludo::getPlayer(int i){
	return (LudoPlayer*)(this->player(i));
}


LudoBoard* Ludo::c_getMainBoard(){
	return (LudoBoard *) this->board();
}



// ======================== Méthodes d'affichage du plateau de jeu ========================

int Ludo::printval(int pos, int PlayerID, int place){

	int res=-1;
	if (pos==-1){
                if(PlayerID< this->getRequiredPlayers() && this->c_getMainBoard()->getPlayerHome(PlayerID)[place]!=NULL){
                        res=(PlayerID*10)+c_getMainBoard()->getPlayerHome(PlayerID)[place]->getNumber();
		}
	}
	else if (pos>=0 && pos<=51){
                if(PlayerID< this->getRequiredPlayers() && c_getMainBoard()->c_getBoardBox(pos)!=NULL){
                        res=(c_getMainBoard()->c_getBoardBox(pos)->getPieceColor()*10)+c_getMainBoard()->c_getBoardBox(pos)->getNumber();
		}
	}
	else if(PlayerID< this->getRequiredPlayers()){
                if(c_getMainBoard()->getPlayerBridge(PlayerID)[place] !=NULL){
                        res=((c_getMainBoard()->getPlayerBridge(PlayerID)[place]->getPieceColor())*10)+c_getMainBoard()->getPlayerBridge(PlayerID)[place]->getNumber();
		}
	}
	return res;
}

const char * Ludo::g(int pos, int PlayerID, int place){
	
	int value=printval(pos,  PlayerID, place);
	if (value==-1){return "__";}
	else if (value==0){return "\033[31m_1\033[0;0m";}
	else if (value==1){return "\033[31m_2\033[0;0m";}
	else if (value==2){return "\033[31m_3\033[0;0m";}
	else if (value==3){return "\033[31m_4\033[0;0m";}
	
	else if (value==10){return "\033[32m_1\033[0;0m";}
	else if (value==11){return "\033[32m_2\033[0;0m";}
	else if (value==12){return "\033[32m_3\033[0;0m";}
	else if (value==13){return "\033[32m_4\033[0;0m";}
	
	else if (value==20){return "\033[33m_1\033[0;0m";}
	else if (value==21){return "\033[33m_2\033[0;0m";}
	else if (value==22){return "\033[33m_3\033[0;0m";}
	else if (value==23){return "\033[33m_4\033[0;0m";}
	
	
	else if (value==30){return "\033[34m_1\033[0;0m";}
	else if (value==31){return "\033[34m_2\033[0;0m";}
	else if (value==32){return "\033[34m_3\033[0;0m";}
	else if (value==33){return "\033[34m_4\033[0;0m";}
	else{return "__";}
}

void Ludo::showIt(){
	//en partant du nord et dans le sens des aiguilles d'une montre 0,3,2,1
 
	cout<<" _______________________________________________"<<endl;
	
	cout<<"|N°4  \033[32m/  \\\033[0;0m         |"<<g(49, -1, -1)<<"|"<<g(50, -1, -1)<<"|"<<g(51, -1, -1)<<"|       \033[31m/  \\\033[0;0m     N°1|"<<endl;
	
	cout<<"|    \033[32m/\033[0;0m"<<g(-1, 1, 0)<<g(-1, 1, 1)<<"\033[32m\\ \033[0;0m       |"<<g(48, -1, -1)<<"|"<<g(100, 0, 0)<<"|"<<g(0, -1, -1)<<"|      \033[31m/\033[0;0m"<<g(-1, 0, 0)<<g(-1, 0, 1)<<"\033[31m\\\033[0;0m       |"<<endl;
	
	cout<<"|    \033[32m\\\033[0;0m"<<g(-1, 1, 2)<<g(-1, 1, 3)<<"\033[32m/ \033[0;0m       |"<<g(47, -1, -1)<<"|"<<g(101, 0, 1)<<"|"<<g(1, -1, -1)<<"|      \033[31m\\\033[0;0m"<<g(-1, 0, 2)<<g(-1, 0, 3)<<"\033[31m/\033[0;0m       |"<<endl;
	
	cout<<"|     \033[32m\\  / \033[0;0m        |"<<g(46, -1, -1)<<"|"<<g(102, 0, 2)<<"|"<<g(2, -1, -1)<<"|       \033[31m\\  /\033[0;0m        |"<<endl;
		
	cout<<"|      \033[32m\\/ \033[0;0m         |"<<g(45, -1, -1)<<"|"<<g(103, 0, 3)<<"|"<<g(3, -1, -1)<<"|        \033[31m\\/\033[0;0m         |"<<endl;
	
	cout<<"| _________________|"<<g(44, -1, -1)<<"|"<<g(104, 0, 4)<<"|"<<g(4, -1, -1)<<"|___________________|"<<endl;
	
	cout<<"||"<<g(38, -1, -1)<<"|"<<g(39, -1, -1)<<"|"<<g(40, -1, -1)<<"|"<<g(41, -1, -1)<<"|"<<g(42, -1, -1)<<"|"<<g(43, -1, -1)<<"|         |"<<g(5, -1, -1)<<"|"<<g(6, -1, -1)<<"|"<<g(7, -1, -1)<<"|"<<g(8, -1, -1)<<"|"<<g(9, -1, -1)<<"|"<<g(10, -1, -1)<<"||"<<endl;
	
	cout<<"||"<<g(37, -1, -1)<<"|"<<g(100, 1, 0)<<"|"<<g(101, 1, 1)<<"|"<<g(102, 1, 2)<<"|"<<g(103, 1, 3)<<"|"<<g(104, 1, 4)<<"|         |"<<g(104, 3, 4)<<"|"<<g(103, 3, 3)<<"|"<<g(102, 3, 2)<<"|"<<g(101, 3, 1)<<"|"<<g(100, 3, 0)<<"|"<<g(11, -1, -1)<<"||"<<endl;//3
	
	cout<<"||"<<g(36, -1, -1)<<"|"<<g(35, -1, -1)<<"|"<<g(34, -1, -1)<<"|"<<g(33, -1, -1)<<"|"<<g(32, -1, -1)<<"|"<<g(31, -1, -1)<<"|_________|"<<g(17, -1, -1)<<"|"<<g(16, -1, -1)<<"|"<<g(15, -1, -1)<<"|"<<g(14, -1, -1)<<"|"<<g(13, -1, -1)<<"|"<<g(12, -1, -1)<<"||"<<endl;
	
	cout<<"|                  |"<<g(30, -1, -1)<<"|"<<g(104, 2, 4)<<"|"<<g(18, -1, -1)<<"|                   |"<<endl;
	
	cout<<"|      \033[33m/\\\033[0;0m          |"<<g(29 ,-1, -1)<<"|"<<g(103, 2, 3)<<"|"<<g(19, -1, -1)<<"|        \033[34m/\\\033[0;0m         |"<<endl;
	 
	cout<<"|     \033[33m/  \\\033[0;0m         |"<<g(28, -1, -1)<<"|"<<g(102, 2, 2)<<"|"<<g(20, -1, -1)<<"|       \033[34m/  \\\033[0;0m        |"<<endl;
	
	cout<<"|    \033[33m/\033[0;0m"<<g(-1, 2, 0)<<g(-1, 2, 1)<<"\033[33m\\ \033[0;0m       |"<<g(27, -1, -1)<<"|"<<g(101, 2, 1)<<"|"<<g(21, -1, -1)<<"|      \033[34m/\033[0;0m"<<g(-1, 3, 0)<<g(-1, 3, 1)<<"\033[34m\\\033[0;0m       |"<<endl;
	
	cout<<"|    \033[33m\\\033[0;0m"<<g(-1, 2, 2)<<g(-1, 2, 3)<<"\033[33m/ \033[0;0m       |"<<g(26, -1, -1)<<"|"<<g(100, 2, 0)<<"|"<<g(22, -1, -1)<<"|      \033[34m\\\033[0;0m"<<g(-1, 3, 2)<<g(-1, 3, 3)<<"\033[34m/\033[0;0m       |"<<endl;
	 
	cout<<"|\033[4mN°3\033[0;0m__\033[33m\\\033[0;0m__\033[33m/\033[0;0m_________|"<<g(25, -1, -1)<<"|"<<g(24, -1, -1)<<"|"<<g(23, -1, -1)<<"|_______\033[34m\\\033[0;0m__\033[34m/\033[0;0m_____\033[4mN°2\033[0;0m|"<<endl;
	

}

// ======================== Méthode de debugage affichant toutes les infos du jeu ========================

void Ludo::checkdata(){
	// Méthode de débuggage affichant toutes les informations du jeu.
	for (int i = 0; i < this->getRequiredPlayers(); i++){
		cout << endl << "Pieces du joueur " << i+1 << endl;
		getPlayer(i)->showPiecesPosition();
	}
	cout << endl << "BOARD: "<<endl;
	for (int i = 0; i < 52; i++){
		if(c_getMainBoard()->getBoard()[i] != NULL)
			cout << i<<":"<<"piece N° "<<c_getMainBoard()->c_getBoardBox(i)->getNumber() +1<<" du joueur "<<c_getMainBoard()->c_getBoardBox(i)->getPieceColor()+1<<endl;
		else
			cout <<i<<":"<<"NULL"<<endl;
	}
	cout << endl << endl << "BRIDGES : "<<endl;
	for (int i = 0; i <this->getRequiredPlayers(); i++){
		cout<<"bridge du joueur"<<i<<endl;
		for (int j = 0; j < 5; j++){
			if (c_getMainBoard()->getPlayerBridgeBox(i, j) != NULL)
				cout << j+100<<":"<<"piece N° "<<c_getMainBoard()->getPlayerBridgeBox(i,j)->getNumber() +1<<" du joueur "<<c_getMainBoard()->getPlayerBridgeBox(i,j)->getPieceColor()+1<<endl;
			else
				cout <<j+100<<":"<<"NULL"<<endl;
		}
		cout << endl;
	}
	cout  << endl << "HOMES : "<< endl;
	for (int i = 0; i < this->getRequiredPlayers(); i++){
		cout<<"home du joueur"<<i<<endl;
		for (int j = 0; j < 4; j++){
			if (c_getMainBoard()->getPlayerHome(i)[j]!=NULL)
				cout <<"piece dans le home à la place:"<< c_getMainBoard()->getPlayerHome(i)[j]->getNumber()<<endl;
			else
				cout << "NULL"<<endl;
		}
		cout << endl;
	}
	cout << endl;
}
// ========================================================================================================



bool Ludo::endOfGame(){
	return this->winner() != -1;
}

bool Ludo::endOfTurn(){
	
	return (this->getDice() != 6);
}

Move* Ludo::parseMove(string data){

	return new LudoMove(data);


}

void Ludo::makeMove(Move* move){
	LudoMove* cast = (LudoMove*)move;
	this->move(cast->start(),cast->finish(),cast->piece(),cast->owner());
	this->displayBoard();
}

void Ludo::runActiveTurn(){
	LudoMove* move = new LudoMove(-107,-107,-107,-107);
	cout<<"C'est ton tour"<<endl;

    this->resetPlayablePieces();
	this->setDice(this->rollDice());
	cout<<"Tu as lancé un "<<this->getDice()<<endl;
	while (this->getDice() == 6){
		
            this->resetPlayablePieces();
		
		for (int i=0;i<4;i++){
            this->_isPlayablePieces[i]=this->playable(this->getPlayer(this->id())->getPiece(i));
			
		}
		
        if (this->YouCanPlay()){
		int ChosenPiece=-2, start=-2, finish=-2;
		
        ChosenPiece=this->getChosenPiece();
		start=this->getPlayer(this->id())->getPiece(ChosenPiece-1)->getPosition();
		if (start==-1){
		finish = ((52-(this->id() * 13))%52);
		}
		else{
			finish=start+this->getDice();
		}
		move = new LudoMove(start,finish,ChosenPiece-1,this->id());
		this->handleMove(move);
			
		}
		else{
			this->endActiveTurn();
			return;
		}
		
		this->setDice(this->rollDice());
		
		
		
		cout<<"Tu as lancé un "<<this->getDice()<<"--------------------------------------------------------------------------"<<endl;
		
	}
	
	
	for (int i=0;i<4;i++){
                this->_isPlayablePieces[i]=this->playable(this->getPlayer(this->id())->getPiece(i));
			
	}
	
	
    if (this->YouCanPlay()){
	int ChosenPiece=-2, start=-2, finish=-2;

            ChosenPiece=this->getChosenPiece();
	start=this->getPlayer(this->id())->getPiece(ChosenPiece-1)->getPosition();
	if (start==-1){
		finish = ((52-(this->id() * 13))%52);
	}
	else{
		finish=start+this->getDice();
	}

	move = new LudoMove(start,finish,ChosenPiece-1,this->id());
	this->handleMove(move);
	
	}
	else{
		this->endActiveTurn();
	}
	
	
	

}



int Ludo::getChosenPiece(){
	string message="";
	
	int ChosenPiece;			
	cin >> ChosenPiece;
        while ((((ChosenPiece-1) < 0) || ((ChosenPiece-1) > 4) || !this->_isPlayablePieces[ChosenPiece-1])){
		cout << "Tu as choisis un mauvais pion, choisis parmis ceux ci : ";
                DisplayPlayablePieces();
		cin >> ChosenPiece;
	}
		
	return ChosenPiece;
}


void Ludo::displayBoard(){

	this->showIt();
}



bool Ludo::playable(LudoPiece* piece){
	
	bool res=false;
	
	if (this->getDice()==6){
		if (this->isInHome(piece)){
			if (this->startPointIsOk()){//vérifie si le point de départ des pions des joueurs est NULL ou occupé par un pion d'un autre joueur
				res=true;
			}
		}
		else{
			res=this->arrivalPointIsOk(piece);
		
		}
	}
	else{//si dé !=6
		if (!this->isInHome(piece)){
			if(this->arrivalPointIsOk(piece)){
				res=true;
			}
		}
	}
	
	return res;

}

bool Ludo::isInHome(LudoPiece* piece){return piece->getPosition()==-1;}


bool Ludo::startPointIsOk(){
        LudoPiece* StartingPoint = c_getMainBoard()->c_getBoardBox(((52-((this->id())*13))%52));
	return StartingPoint == NULL or StartingPoint->getPieceColor() != this->id();
}

bool Ludo::arrivalPointIsOk(LudoPiece* piece){
	bool res = false;
	int start = piece->getPosition() , finish = (start + this->getDice()) , jumpOnBridge = ((52-(this->id()*13))-2) ;
	
	if (start<=jumpOnBridge && finish > jumpOnBridge){
		if ( !( start==jumpOnBridge && this->getDice() ==6 ) ){//si on ne va pas trop loin dans le bridge
			res=this->myBridgePosIsFree(finish-jumpOnBridge-1);
		}
	}
	else if (start>=100){
		if (finish<=104){//si on ne va pas trop loin
			res=this->myBridgePosIsFree(finish-100);
		}
	}
	
	else{
		
		res=boardPosIsFree(finish%52);
	}
	return res;


}

bool Ludo::myBridgePosIsFree(int i){

	return this->c_getMainBoard()->getPlayerBridge(this->id())[i]==NULL;

}

bool Ludo::boardPosIsFree(int i){
	
	
	return this->noPieceOnBoard(i) or ( ((LudoPiece*) (this->c_getMainBoard()->c_getBoardBox(i))) ->getPieceColor() != this->id() );

}

bool Ludo::noPieceOnBoard(int i){

	return (this->c_getMainBoard()->c_getBoardBox(i)==NULL);
}





















