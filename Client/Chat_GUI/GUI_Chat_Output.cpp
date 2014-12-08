#include "GUI_Chat_Output.h"
#include <QScrollBar>

GUI_Chat_Output::GUI_Chat_Output():__placeHolder("<font color='#aaa'>Il n'y a encore aucun message</font>"),__empty(true){
    this->setReadOnly(true);
    this->setText(this->__placeHolder);
    //this->setTextColor("");
}

GUI_Chat_Output& GUI_Chat_Output::addText(QString text){
    if (this->__empty){
        this->setText("");
        this->__empty = false;
    }
    this->setText(this->toPlainText()+text+"\n");
    this->verticalScrollBar()->setValue(this->verticalScrollBar()->maximum());
    return *this;
}
