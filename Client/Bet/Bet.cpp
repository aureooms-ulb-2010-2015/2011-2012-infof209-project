#include "Bet.hpp"
#include "../../Common/Request.hpp"

using namespace std;


Bet::Bet(GameServer* gameServer){
	this->listOfBets = new vector< pair<string,string> >;
	this->_gameServer = gameServer;
}

Bet::~Bet(){

}

void Bet::route(Request * request){
    if(request->getName()=="askAmount"){
        this->askAmount();
    }
    else if(request->getName() == "addBet"){
        this->addBetToList(request);
    }
    else if(request->getName() == "validate"){
        this->askValidation();
    } 
}

GameServer* Bet::getGameServer(){
	return this->_gameServer;
}

void Bet::addBetToList(Request* r){	
	if (r->getAttributes().size() >= 2)
		this->listOfBets->push_back(make_pair(r->getAttributes()[0],r->getAttributes()[1]));
}

void Bet::displayWait(){
	cout<<"En attende des mises des autres joueurs..."<<endl;
}

void Bet::displayValid(){
	cout<<"Tout le monde a accepté les mises !"<<endl;
}

void Bet::displayNotValid(){
	cout<<"Les mises n'ont pas été acceptées par tous les joueurs"<<endl;
}

void Bet::displayBets(){
	for(int i = 0; i < this->listOfBets->size();++i)
	{
		cout<<(*listOfBets)[i].first<<" a misé "<<(*listOfBets)[i].second<<endl;
	}
}

void Bet::askAmount(){
	Request request(this->getGameServer());
	int amount = 0;
	*this->promptInput("Combien voulez vous miser ?") >> amount;
	if (amount != -1){
		ostringstream temp;
		temp << amount;
		request.makeRequest("BET",temp.str().c_str());
		request.flush();
	}	
}

void Bet::askValidation(){
	this->displayBets();
	this->listOfBets->clear();
	string validation;
	while( (validation != "o" ) && (validation != "n")){
	    *this->promptInput("Acceptez-vous les mises ?(o/n)")>>validation;
	}
	if(validation == "o"){
	    Request request(this->getGameServer());
	    request.makeRequest("BET","validate");
	    request.addAttribute("true");
	    request.flush();
	}
	else{
	    Request request(this->getGameServer());
	    request.makeRequest("BET","validate");
	    request.addAttribute("false");
	    request.flush();
	}
}

void Bet::promptPause(string message){
	cout << message << " (entrée)";
	string pause;
	getline(cin,pause);
	this->clearInputStream();
}

bool Bet::validInputStream(){
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
void Bet::clearInputStream(){
	cin.clear();
	cin.seekg(0,ios::end);
	if (!cin.fail()){
		cin.ignore(numeric_limits<streamsize>::max());
	}
	else{
		cin.clear();
	}
}

istringstream* Bet::promptInput(string message){
	cout << message;
	string temp;
	getline(cin,temp);
	this->validInputStream();
	this->clearInputStream();
	return new istringstream(temp);
}

vector< pair<string, string> >* Bet::getListOfBets(){
	return listOfBets;
}
