#include "GUI_Chat_Input.h"

GUI_Chat_Input::GUI_Chat_Input(){
    QObject::connect(this, SIGNAL(returnPressed()), this, SLOT(send()));
    this->setText("");
    this->setMinimumHeight(23);
}

void GUI_Chat_Input::send(){
    emit send(this->text());
    this->setText("");
    this->setFocus();
}

