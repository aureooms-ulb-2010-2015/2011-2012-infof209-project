#include "Backgammon.hpp"

#include <sstream>
#include <stdio.h>
#include <stdlib.h>


#include "BackgammonMove.hpp"

using namespace std;

Backgammon::Backgammon(GameServer* server) : DiceGame(server,2,new BackgammonBoard()),currentDice({0,0,0,0}) {
	
	this->players()->push_back(new BackgammonRedPlayer());
	this->players()->push_back(new BackgammonBlackPlayer());
	
	//this->c_player = (BackgammonPlayer*)(this->player(this->id()));
	
}

Backgammon::~Backgammon(){}

int Backgammon::winner(){
	
	if (this->c_board()->getExitedPieces(0) == 15){
		return 0;
	}
	else if (this->c_board()->getExitedPieces(1) == 15){
		return 1;
	}
	else{
		return -1;
	}
}

unsigned short int Backgammon::otherPlayerIndex(){
	return this->nextPlayer();
}

bool Backgammon::exists(int point){
	return (point >= 0) && (point < 24);
}

string Backgammon::getPoint(int point){
	if(!this->exists(point)){
		return "";
	}
	return this->c_board()->getContent(point);
}


string Backgammon::getPointColor(int point){	
	if(!this->exists(point)){
		return "U";
	}
	if (this->emptyPoint(point)){
		return "E";
	}
	return ((BackgammonPiece*)(this->c_board()->getPieceInCell(point,0)))->letter();
}

bool Backgammon::redPoint(int point){
	if(!this->exists(point)){
		return false;
	}
	return this->getPointColor(point) == "R";
}


bool Backgammon::blackPoint(int point){
	if(!this->exists(point)){
		return false;
	}
	return this->getPointColor(point) == "B";
}


bool Backgammon::emptyPoint(int point){
	if(!this->exists(point)){
		return false;
	}
	return this->c_board()->getNumberOfPieces(point) == 0;
}

bool Backgammon::owned(int point){
	if(!this->exists(point)){
		return false;
	}

	return ( this->c_player()->red() && this->redPoint(point) )
	|| ( this->c_player()->black() && this->blackPoint(point) );
}

bool Backgammon::ownedByOther(int point){
	if(!this->exists(point)){
		return false;
	}

	return (!this->owned(point)) && (!this->emptyPoint(point));
}

bool Backgammon::catchable(int point){
	if(!this->exists(point)){
		return false;
	}
	return (!this->ownedByOther(point)) || (this->c_board()->getNumberOfPieces(point) == 1);
}

bool Backgammon::exitPoint(int point){
	if(!this->exists(point)){
		return false;
	}
	
	return (this->c_player()->multiplier()*point) > (this->c_player()->multiplier()*(this->c_player()->exitValue()-this->c_player()->multiplier()*7));
}

bool Backgammon::enterPoint(int point){
	if(!this->exists(point)){
		return false;
	}

	return (this->c_player()->multiplier()*point) < (this->c_player()->multiplier()*(this->c_player()->startValue()+this->c_player()->multiplier()*6));
}
BackgammonPiece* Backgammon::topPiece(int point){
	if(!this->exists(point)){
		return NULL;
	}

	if (this->emptyPoint(point)){
		return NULL;
	}


	unsigned int j = 0;
	while (this->board()->getPieceInCell(point,j) != NULL) {
		j++;
	}
	return (BackgammonPiece*)(this->board()->getPieceInCell(point,j-1));
}

BackgammonPiece* Backgammon::popPiece(int point){

	BackgammonPiece* piece = this->topPiece(point);

	if (piece == NULL){
		return NULL;
	}

	this->c_board()->removePiece(point,this->c_board()->getNumberOfPieces(point)-1);
	return piece;
}

bool Backgammon::sameColor(int from, int to){
	return (this->redPoint(from) && this->redPoint(to))
		||(this->blackPoint(from) && this->blackPoint(to));
}

void Backgammon::movePiece(int from, int to){
	this->c_board()->addPiece(to,this->c_board()->getNumberOfPieces(to),this->popPiece(from));
}


void Backgammon::normalMove(int from, int to){
	
	if (this->sameColor(from-1,to-1) || this->emptyPoint(to-1)) {  
		this->movePiece(from-1,to-1);
	}
	
	
	else{
		unsigned short int index = (this->redPoint(to-1))?0:1;
		this->c_board()->setEatenPieces(index,1);
		this->c_board()->removePiece(to-1,0);
		this->movePiece(from-1,to-1);
	}
}

void Backgammon::moveFromEaten(int emptyPoint,string color){
	if (this->emptyPoint(emptyPoint-1)) {
		if (color == "B"){
			this->c_board()->addPiece(emptyPoint-1,0, new BackgammonBlackPiece());
			this->c_board()->setEatenPieces(1,-1);
		}
		
		else {
			this->c_board()->addPiece(emptyPoint-1,0,new BackgammonRedPiece());
			this->c_board()->setEatenPieces(0,-1);
		}
	}
	
	else if (color == this->getPointColor(emptyPoint-1)) {  
		
		int i = 0;
		while (this->c_board()->getPieceInCell(emptyPoint-1,i) != NULL) {
			i++;
		}
		if (color == "B"){
			this->c_board()->addPiece(emptyPoint-1,i, new BackgammonBlackPiece());
			this->c_board()->setEatenPieces(1,-1);
		}
		
		else {
			this->c_board()->addPiece(emptyPoint-1,i, new BackgammonRedPiece());
			this->c_board()->setEatenPieces(0,-1);
		}
	}
	
	else {
	
		
		if (this->c_board()->getNumberOfPieces(emptyPoint-1) == 1) {
			
			if (color == "R") {
				this->c_board()->setEatenPieces(0,-1);
				this->c_board()->setEatenPieces(1,1);
				this->c_board()->removePiece(emptyPoint-1,0);
				this->c_board()->addPiece(emptyPoint-1,0,new BackgammonRedPiece());
			}
			
			else {
				this->c_board()->setEatenPieces(1,-1);
				this->c_board()->setEatenPieces(0,1);
				this->c_board()->removePiece(emptyPoint-1,0);
				this->c_board()->addPiece(emptyPoint-1,0,new BackgammonBlackPiece());
			}
		}
	}	
}

void Backgammon::exitMove(int exitPoint){
	//Function to exit a piece out of the board.
	
	int i=0;
	while ( this->c_board()->getPieceInCell(exitPoint-1,i) != NULL){
		i++;
	}
	unsigned short int index = (this->redPoint(exitPoint-1))?0:1;
	this->c_board()->removePiece(exitPoint-1,i-1);	
	this->c_board()->setExitedPieces(index,1);

}

bool Backgammon::mayExitPieces(){

	if (this->mustEnterPieces()){
		return false;
	}
	
	for(int	i=this->c_player()->startValue();
		(!this->exitPoint(i));
		i+=this->c_player()->multiplier()){

		if ( this->owned(i) ){
			return false;
		}

	}

	return true;
}

bool Backgammon::canExitPieces(){
	for (unsigned short int j = 0;j<4;j++){
		if (this->currentDice[j] == 0){
			continue;
		}

		short int k = this->c_player()->exitValue();
		k -= this->c_player()->multiplier()*this->currentDice[j];
		
		if ( this->owned(k) ){
			return true;
		}

	}
	return false;
}

bool Backgammon::mustEnterPieces(){
	
	return this->c_board()->getEatenPieces(this->id()) > 0;

}

bool Backgammon::canEnterPieces(){
	for (unsigned short int j = 0;j<4;j++){
		if (this->currentDice[j] == 0){
			continue;
		}

		unsigned short int k = this->c_player()->startValue();
		k += (this->currentDice[j]-1) * this->c_player()->multiplier();

		if(this->catchable(k)){
			return true;
		}

	}

	return false;
}

bool Backgammon::canMakeNormalMove(){

	for (unsigned short int j = 0;j<4;j++){
		if (this->currentDice[j] == 0){
			continue;
		}
		for (int i = 0; i < 24 ; i++) {
			if(this->owned(i)){
				if(this->catchable(i+this->c_player()->multiplier()*this->currentDice[i])){
					return true;
				}
			}
		}
	}
	return false;
}


string Backgammon::buildMove(int dice){
	
	ostringstream temp;
	
	
	if ( this->mustEnterPieces() ) {
		unsigned short int point = this->askEnterPoint();
		this->displayTurn();
		
		if(!this->catchable(point-1)){
		
			this->promptPause("Vous ne pouvez pas jouer ici, choisissez un autre endroit. ");
		}
		else if(this->c_player()->startValue()+(dice-1)*this->c_player()->multiplier() == point-1){
			temp << this->id() << "F:" << this->c_player()->letter() << ":" << point;
		}
		else{
			this->promptPause("Le déplacement ne correspond pas au dé choisi!");
		}
	}

	else if (this->mayExitPieces()) {
		int exitPoint = this->askExitPoint();
		this->displayTurn();
		if (exitPoint+dice*this->c_player()->multiplier() != this->c_player()->exitValue() )
			this->promptPause("Le déplacement ne correspond pas au dé choisi!");
		else {
			temp << this->id() << "E:" << exitPoint;
		}
	}

	else {
		unsigned short int from = this->askFromPoint();
		this->displayTurn();
		unsigned short int to = this->askToPoint();
		this->displayTurn();

		if(this->c_player()->multiplier()*(to-from) != dice)
			this->promptPause("Le déplacement ne correspond pas au dé choisi!");
		
		else if (this->owned(from-1) && this->catchable(to-1)){
			temp << this->id() << "N:" << from << " " << to;
		}

		else{
			this->promptPause("Ce mouvement est incorrect.");
		}
	}
	return temp.str();
}

bool Backgammon::noPossibleMove(){

	if (this->mustEnterPieces()){
		if(!this->canEnterPieces()){
			return true;
		}
		return false;
	}

	if (this->mayExitPieces()){
		if(!this->canExitPieces()){
			return true;
		}
		return false;
	}

	return !this->canMakeNormalMove();
}

BackgammonBoard* Backgammon::c_board(){
	return (BackgammonBoard*)this->board();
}
BackgammonPlayer* Backgammon::c_player(){
	return (BackgammonPlayer*)(this->player(this->id()));
}

bool Backgammon::endOfGame(){
	return this->winner() != -1;
}

bool Backgammon::endOfTurn(){
	return !this->diceLeft();
}

Move* Backgammon::parseMove(string data){
	return new BackgammonMove(data);
}

void Backgammon::makeMove(Move* move){

	BackgammonMove* cast = (BackgammonMove*)move;
	if(cast->type() == "E"){
		this->exitMove(cast->exit_p());
	}
	else if(cast->type() == "F"){
		this->moveFromEaten(cast->empty_p(),cast->color());
	}
	
	else{
		this->normalMove(cast->from(),cast->to());
	}

}

bool Backgammon::diceLeft(){
	return (this->currentDice[0]!=0)
	||(this->currentDice[1]!=0)
	||(this->currentDice[2]!=0)
	||(this->currentDice[3]!=0);
}

void Backgammon::resetDices(){
	for (unsigned short int i = 0;i < 4;i++){
		this->currentDice[i] = 0;
	}
}

void Backgammon::displayDices(){
	cout << endl << " 1 2 3 4" << endl << " ";
	for (int i=0; i<4; i++) {
		if (this->currentDice[i] != 0)
			cout << this->currentDice[i] << " ";
		else
			cout << "_ ";
	
	}
	cout << endl << endl;
}

void Backgammon::copyDices(){

	this->currentDice[2] = this->currentDice[0];
	this->currentDice[3] = this->currentDice[0];
}

void Backgammon::rollDices(){

	this->currentDice[0] = this->rollDice();
	this->currentDice[1] = this->rollDice();

	if (this->rolledDouble()) {
		cout << "Vous avez fait un double " << currentDice[0] << " !" << endl;;
		this->copyDices();
	}
}

bool Backgammon::rolledDouble(){
	return ( this->currentDice[0] == this->currentDice[1] );
}

bool Backgammon::wrongDiceChoice(unsigned short int choice){
	return (choice == 0) || (choice>4) || (this->currentDice[choice-1] == 0);
}

unsigned short int Backgammon::askDice(){
	unsigned short int choice = 0;
	*this->promptInput("Choisissez le dé que vous souhaitez jouer : ") >> choice;
	return choice;
}

unsigned short int Backgammon::askPoint(string qual){
	unsigned short int choice = 0;
	ostringstream temp;
	temp << "Choisissez la case " << qual << " : " ;
	*this->promptInput(temp.str()) >> choice;
	return choice;
}

unsigned short int Backgammon::askFromPoint(){
	return this->askPoint("de départ");
}

unsigned short int Backgammon::askToPoint(){
	return this->askPoint("d'arrivée");
}


unsigned short int Backgammon::askExitPoint(){
	return this->askPoint("de laquelle sortir une dame");
}


unsigned short int Backgammon::askEnterPoint(){
	return this->askPoint("sur laquelle poser une dame");
}

void Backgammon::runActiveTurn(){

	this->rollDices();

	do{

		this->displayMessage("Voici les dés disponibles : ");
		this->displayDices();
	
		if (this->noPossibleMove()) {
			this->promptPause("Aucun mouvement possible avec cette combinaison de dés");
			this->resetDices();
			this->endActiveTurn();
			break;
		}
	
		else{
		
			unsigned short int choice = this->askDice();
			if(this->wrongDiceChoice(choice)){
				this->promptPause("Ce dé ne peut pas être joué!");
				this->displayTurn();
				continue;
			}
			this->displayTurn();
			string data = this->buildMove(this->currentDice[choice-1]);
			if (data != ""){
				this->currentDice[choice-1] = 0;
				BackgammonMove* move = new BackgammonMove(data);
				this->handleMove(move);
			}

			if(!this->endOfTurn()){
				this->displayTurn();
			}
		}
	}while(!this->endOfTurn());
}
