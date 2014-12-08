#ifndef GUI_CHAT_INPUT_H
#define GUI_CHAT_INPUT_H

#include <QLineEdit>
#include "GUI_Chat_Output.h"

class GUI_Chat_Input: public QLineEdit{

Q_OBJECT

public:

    GUI_Chat_Input();

public slots:

    void send();

signals:

    void send(QString);


};

#endif // GUI_CHAT_INPUT_H
