#include "Game.hpp"
#include "Move.hpp"
#include "../GameServer.hpp"

#include <stdlib.h>
#include <limits>
#include <sstream>

//STATIC MEMBERS

const short int Game::VIEWER_ID = -1;
const short int Game::NO_WINNER = -1;

//BUILD
Game::Game(GameServer* server, unsigned int numberOfPlayers, Board* board):_server(server),_request(new Request(server)),_id(-1),_numberOfPlayers(numberOfPlayers),_board(board), _players(new vector<GamePlayer*>()),_connectedPlayers(0),_running(true),_currentPlayerId(0){}

//GET
int Game::id(){
	return this->_id;
}

GameServer* Game::server(){
	return this->_server;
}

Request* Game::request(){
	return this->_request;
}

Board* Game::board(){
	return this->_board;
}
int Game::getRequiredPlayers(){
	return this->_numberOfPlayers;
}
unsigned int Game::getConnectedPlayers(){
	return this->_connectedPlayers;
}


void Game::setConnectedPlayers(unsigned int n){
	this->_connectedPlayers = n;
}

bool Game::running(){
	return this->_running;
}

//PLAYER GETTERS

vector<GamePlayer*>* Game::players(){
	return this->_players;
}

GamePlayer* Game::player(unsigned short int index){
	return this->players()->at(index);
}

GamePlayer* Game::currentPlayer(){
	return this->player(this->_currentPlayerId);
}

//SET
void Game::server(GameServer * server){
	this->_server = server;
}
void Game::id(int id){
	this->_id = id;
}

//CHECKS


//BEFORE START


void Game::waitForBegin(){
	this->clear();
	ostringstream temp;
	temp << "En attente d'autres joueurs\t";
	temp << this->getConnectedPlayers() << "/" << this->getRequiredPlayers();
	temp << " connecté(s)";
	this->displayMessage(temp.str());
	this->displayBoard();
}

//RECEIVING DATA

void Game::refresh(Request* history){
	
	string data;
	data = history->getAttributes()[0];
	this->refresh(data);
}

void Game::refresh(string data){
	if(data != "!!!" && data != "."){
		Move* move = this->parseMove(data);
		this->makeMove(move);
		delete move;
	}
	this->displayTurn();
}

//SENDING DATA



void Game::propage(Move* move){
	this->server()->sendMove(move->serialize());
}

void Game::handleMove(Move* move){
	this->makeMove(move);
	this->propage(move);

	if (this->endOfGame()){
		this->request()->set("winner",this->winner());
		this->endActiveTurn();
	}

	else if(this->endOfTurn()){
		this->endActiveTurn();
	}
}

//PLAY (PLAYER MAIN)


unsigned int Game::nextPlayer(){
	return (this->id()+1)%this->getRequiredPlayers();
}

bool Game::endOfTurn(){
	return true;
}
void Game::endActiveTurn(){
	this->request()->set("nextTurn",this->nextPlayer());
}



//INPUT
void Game::promptPause(string message){
	cout << message << " (entrée)";
	string pause;
	getline(cin,pause);
	this->clearInputStream();
}

bool Game::validInputStream(){
	if( cin.eof() || cin.bad()){
		cerr << "Une erreur interne est survernue." << endl;
		return false;
	}
	else if (cin.fail()){
		cerr << "Erreur, saisie incorrecte." << endl;
		return false;
	}
	return true;
}
void Game::clearInputStream(){
	cin.clear();
	cin.seekg(0,ios::end);
	if (!cin.fail()){
		cin.ignore(numeric_limits<streamsize>::max());
	}
	else{
		cin.clear();
	}
}

istringstream* Game::promptInput(string message){
	cout << message;
	string temp;
	getline(cin,temp);
	this->validInputStream();
	this->clearInputStream();
	return new istringstream(temp);
}

//OUTPUT

void Game::clear(){
	system("clear");
}

void Game::displayBoard(){
	cout << endl;
	this->board()->display();
	cout << endl;
}

void Game::displayTurn(){
	this->clear();
	ostringstream temp;
	temp << "C'est le tour de : '"<< this->currentPlayer()->toString() <<"'";
	this->displayMessage(temp.str());
	this->displayBoard();
}

void Game::displayEndOfGame(){
	this->clear();
	this->displayMessage("Fin de la partie");
	this->displayBoard();
	this->displayWinner();
	this->displayScore();
	this->_running = false;
}

void Game::displayWinner(){
	
	if (this->winner() == Game::NO_WINNER){
		this->displayMessage("C'est un match nul");
	}
	else{
		ostringstream temp;
		temp << "Le gagnant est : '"<< this->player(this->winner())->toString() <<"'";
		this->displayMessage(temp.str());
	}
}

void Game::displayMessage(string message){
	cout << message << endl;
}
void Game::displayScore(){}

//ASYNC REQUEST HANDLER

void Game::route(Request* request){
	if(!this->running()){return;}

	string name = request->getName();
	string attribute = request->getAttributes()[0];
	
	if(name == "setId"){
		int id = 0;
		istringstream temp(attribute);
		temp >> id;
		this->id(id);
	}
	else if(name == "runActiveTurn"){
		this->runActiveTurn();
	}
	else if (name == "refresh"){
		this->refresh(request);
	}
	else if (name == "display"){
		this->displayTurn();
	}
	else if (name == "waitForBegin"){
		this->waitForBegin();
	}
	else if (name == "setConnectedPlayers"){
		int n = 0;
		istringstream temp(attribute);
		temp >> n;
		this->setConnectedPlayers(n);
	}
	else if (name == "endOfGame"){
		this->displayEndOfGame();
	}
	else if (name == "setCurrentPlayerId"){
		unsigned short int n = 0;
		istringstream temp(attribute);
		temp >> n;
		this->_currentPlayerId = n;
	}
	else if (name == "kill"){
		this->_running = false;
	}
	else{
		cout << "NON RECONNU : " << request->getSequence() << endl;
	}
	cout << name<< " traité" << endl;
}
