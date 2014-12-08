#ifndef GUI_CHAT_H
#define GUI_CHAT_H

#include <QObject>
#include <QGroupBox>
#include <QGridLayout>
#include "GUI_Chat_Output.h"
#include "GUI_Chat_Input.h"
#include "GUI_Chat_Button.h"
#include "Chat_client_header/Chat_client.h"

class GUI_Chat : public QGroupBox{
    Q_OBJECT

private:
    QGridLayout* __layout;
    GUI_Chat_Output* __output;
    GUI_Chat_Input* __input;
    GUI_Chat_Button* __button;
    Chat_client* __client;

public:
    GUI_Chat();
    GUI_Chat(QWidget* window);
    GUI_Chat(string server, string pseudo, string channel);
    GUI_Chat& init();
};


#endif // GUI_CHAT_H
