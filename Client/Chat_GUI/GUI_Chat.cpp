#include "GUI_Chat.h"

GUI_Chat::GUI_Chat(string server, string pseudo, string channel):QGroupBox("Chat") {
    this->__output = new GUI_Chat_Output();

    this->__button = new GUI_Chat_Button();

    this->__input = new GUI_Chat_Input();

    this->__client = new Chat_client(server, pseudo, channel);

    this->__client->start();


    QObject::connect(this->__button, SIGNAL(clicked()), this->__input, SIGNAL(returnPressed()));
    QObject::connect(this->__input, SIGNAL(send(QString)), this->__client->sender(), SLOT(forward(QString)));
    QObject::connect(this->__client->receiver(), SIGNAL(received(QString)), this->__output, SLOT(addText(QString)));

    this->__layout = new QGridLayout();
    this->__layout->addWidget(this->__output,0,0,1,2);
    this->__layout->addWidget(this->__input,1,0);
    this->__layout->addWidget(this->__button,1,1);

    this->__input->setFocus();
    this->setLayout(this->__layout);
}

GUI_Chat::GUI_Chat():QGroupBox("Chat"){
    this->init();
}

GUI_Chat::GUI_Chat(QWidget* window):QGroupBox("Chat",window){
    this->init();
}

GUI_Chat& GUI_Chat::init(){
    this->__output = new GUI_Chat_Output();

    this->__button = new GUI_Chat_Button();

    this->__input = new GUI_Chat_Input();

    this->__client = new Chat_client();

    this->__client->start();


    QObject::connect(this->__button, SIGNAL(clicked()), this->__input, SIGNAL(returnPressed()));

    QObject::connect(this->__input, SIGNAL(send(QString)), this->__client->sender(), SLOT(forward(QString)));

    QObject::connect(this->__client->receiver(), SIGNAL(received(QString)), this->__output, SLOT(addText(QString)));


    this->__layout = new QGridLayout();
    this->__layout->addWidget(this->__output,0,0,1,2);
    this->__layout->addWidget(this->__input,1,0);
    this->__layout->addWidget(this->__button,1,1);

    this->__input->setFocus();
    this->setLayout(this->__layout);


    return *this;
}
