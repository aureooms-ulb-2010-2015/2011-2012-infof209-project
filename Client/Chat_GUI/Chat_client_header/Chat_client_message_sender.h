#if !defined(_CHAT_CLIENT_MESSAGE_SENDER_H)
#define _CHAT_CLIENT_MESSAGE_SENDER_H


#include "../Library/Thread/Thread.hpp"
#include "Chat_message.h"
#include "../Library/Socket/ClientSocket.h"

#include <QString>
#include <QObject>

class Chat_client;
class Chat_client_message_sender: public QObject{
    Q_OBJECT

private:
	ClientSocket *socket;
	Chat_client *client;
public:
	Chat_client_message_sender(Chat_client *client);
        ~Chat_client_message_sender();
        virtual Chat_client_message_sender& send_message(Chat_message &message);

public slots:
        virtual Chat_client_message_sender& forward(QString text);
};

#endif  //_CHAT_CLIENT_MESSAGE_SENDER_H
