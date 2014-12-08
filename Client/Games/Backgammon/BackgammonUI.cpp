#include "BackgammonUI.hpp"

BackgammonUI::BackgammonUI(GameServer* server):Backgammon(server) {

	setFixedSize(500,500);
	display = new QVBoxLayout(this);
	//display->setSpacing(20);

	dice = new QHBoxLayout();
	dice->setSpacing(2);

	board = new QGridLayout();
	board->setHorizontalSpacing(0);
	board->setVerticalSpacing(0);

	setDice(1,3,0,0);
	display->addLayout(dice);
	
	createBoard();
	createPieces();
	putPiecesOnBoard();
	
	display->addLayout(board);

	this->setLayout(display);
	this->show();
	if(selectedDice==0){
		connect(dice1, SIGNAL(emitDiceNumber(int)),this,SLOT(setSelectedDice(int)));
		connect(dice2, SIGNAL(emitDiceNumber(int)),this,SLOT(setSelectedDice(int)));
		connect(dice3, SIGNAL(emitDiceNumber(int)),this,SLOT(setSelectedDice(int)));
		connect(dice4, SIGNAL(emitDiceNumber(int)),this,SLOT(setSelectedDice(int)));
		if(selectedDice!= 0)
			cout<<"You chose the dice: "<<selectedDice<<endl;
	}
	cout<<"OUT" <<endl;
}

void BackgammonUI::createBoard(){
	QString red = "Red";
	QString white = "White";
	QString red360 = "Red360";
	QString white360 = "White360";
	
	for(int i=0;i<12;++i){
		points[i] = new QVBoxLayout();
		if(i%2 == 0)
			points[i]->addWidget(new Point(white),0);
		else
			points[i]->addWidget(new Point(red),0);
		board->addLayout(points[i],0,i);
	}
	
	int counter = 12;
	for(int i=0;i<12;++i){
		points[counter] = new QVBoxLayout();
		if(i%2 == 0)
			points[counter]->addWidget(new Point(red360),0);
		else
			points[counter]->addWidget(new Point(white360),0);
		board->addLayout(points[counter],1,i);
		counter++;
	}

}

void BackgammonUI::createPieces(){

	for(int i = 0; i<15; ++i){
		backgammonPieces[i] = new QLabel();
		backgammonPieces[i]->setPixmap(QPixmap("./Interface/Images/Backgammon/PionBlancBack.png"));
	}
	for(int i = 15; i<30; ++i){
		backgammonPieces[i] = new QLabel();
		backgammonPieces[i]->setPixmap(QPixmap("./Interface/Images/Backgammon/PionRougeBack.png"));
	}
	
}

void BackgammonUI::putPiecesOnBoard(){
	
	int counter = 0;
	for(int i=12; i<24;i++){
		pawns[i] = new QGridLayout();
		pawns[i]->setHorizontalSpacing(0);
		pawns[i]->setVerticalSpacing(0);
		QSpacerItem* spacer = new QSpacerItem(10,10);
		pawns[i]->addItem(spacer,7,0);
		board->addLayout(pawns[i],0,counter);
		counter++;
	}
	
	counter = 0;
	for(int i=11; i>-1;--i){
		pawns[i] = new QGridLayout();
		pawns[i]->setHorizontalSpacing(0);
		pawns[i]->setVerticalSpacing(0);
		QSpacerItem* spacer = new QSpacerItem(10,10);
		pawns[i]->addItem(spacer,7,0);
		board->addLayout(pawns[i],1,counter);
		counter++;
	}

	pawns[5]->addWidget(backgammonPieces[0],0,0);
	pawns[5]->addWidget(backgammonPieces[1],1,0);
	pawns[5]->addWidget(backgammonPieces[2],2,0);
	pawns[5]->addWidget(backgammonPieces[3],3,0);
	pawns[5]->addWidget(backgammonPieces[4],4,0);

	pawns[7]->addWidget(backgammonPieces[5],0,0);
	pawns[7]->addWidget(backgammonPieces[6],1,0);
	pawns[7]->addWidget(backgammonPieces[7],2,0);

	pawns[12]->addWidget(backgammonPieces[8],0,0);
	pawns[12]->addWidget(backgammonPieces[9],1,0);
	pawns[12]->addWidget(backgammonPieces[10],2,0);
	pawns[12]->addWidget(backgammonPieces[11],3,0);
	pawns[12]->addWidget(backgammonPieces[12],4,0);

	pawns[23]->addWidget(backgammonPieces[13],0,0);
	pawns[23]->addWidget(backgammonPieces[14],1,0);

	pawns[0]->addWidget(backgammonPieces[15],0,0);
	pawns[0]->addWidget(backgammonPieces[16],1,0);

	pawns[11]->addWidget(backgammonPieces[17],0,0);
	pawns[11]->addWidget(backgammonPieces[18],1,0);
	pawns[11]->addWidget(backgammonPieces[19],2,0);
	pawns[11]->addWidget(backgammonPieces[20],3,0);
	pawns[11]->addWidget(backgammonPieces[21],4,0);

	pawns[16]->addWidget(backgammonPieces[22],0,0);
	pawns[16]->addWidget(backgammonPieces[23],1,0);
	pawns[16]->addWidget(backgammonPieces[24],2,0);

	pawns[18]->addWidget(backgammonPieces[25],0,0);
	pawns[18]->addWidget(backgammonPieces[26],1,0);
	pawns[18]->addWidget(backgammonPieces[27],2,0);
	pawns[18]->addWidget(backgammonPieces[28],3,0);
	pawns[18]->addWidget(backgammonPieces[29],4,0);
}

void BackgammonUI::setDice(int x1, int x2, int x3, int x4){

	QString pathToDiceImages = "./Interface/Images/Backgammon/dice/Dice_";
	QString fileFormat = ".png";
	QString dice1QString; QString dice2QString; QString dice3QString; QString dice4QString;
	dice1QString = dice1QString.setNum(x1);
	dice2QString = dice2QString.setNum(x2);
	dice3QString = dice3QString.setNum(x3);
	dice4QString = dice4QString.setNum(x4);

	dice1 = new ClickableQLabel(x1);
	dice1->setPixmap(QPixmap(pathToDiceImages+dice1QString+fileFormat));
	dice2 = new ClickableQLabel(x2);
	dice2->setPixmap(QPixmap(pathToDiceImages+dice2QString+fileFormat));
	dice3 = new ClickableQLabel(x3);
	dice3->setPixmap(QPixmap(pathToDiceImages+dice3QString+fileFormat));
	dice4 = new ClickableQLabel(x4);
	dice4->setPixmap(QPixmap(pathToDiceImages+dice4QString+fileFormat));

	dice->addWidget(dice1);
	dice->addWidget(dice2);
	dice->addWidget(dice3);
	dice->addWidget(dice4);

}

void BackgammonUI::setSelectedDice(int recievedDice){
	selectedDice = recievedDice;
	cout<<selectedDice<<endl;
}
