#ifndef GUI_CHAT_OUTPUT_H
#define GUI_CHAT_OUTPUT_H

#include <string>
#include <QTextEdit>

class GUI_Chat_Output: public QTextEdit{

Q_OBJECT

private:
    QString __placeHolder;
    bool __empty;

public:

    GUI_Chat_Output();

public slots:

    virtual GUI_Chat_Output& addText(QString text);


};

#endif // GUI_CHAT_OUTPUT_H
