#include "GUI_Chat_Button.h"
#include <QFont>
#include <QIcon>

GUI_Chat_Button::GUI_Chat_Button():QPushButton("Envoyer"){
    // Customisation du bouton
    this->setFont(QFont("Helvetica", 10,QFont::Bold));
    this->setCursor(Qt::PointingHandCursor);
    //this->setIcon(QIcon("C:/Users/user/Qt Projets/test-build-desktop-Qt_4_8_0_for_Desktop_-_MinGW__Qt_SDK__Debug/debug/GUI_Chat_send.png"));
    //this->setLayoutDirection(Qt::RightToLeft);
    this->setMinimumHeight(25);
}
