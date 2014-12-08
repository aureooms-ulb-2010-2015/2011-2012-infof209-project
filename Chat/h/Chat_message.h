#if !defined(_CHAT_MESSAGE_H)
#define _CHAT_MESSAGE_H

#include "../h/Feed.h"

using namespace std;

class Chat_message : public Feed{
public:
	Chat_message(long int timestamp,string author,string content);
	Chat_message(string encoded);
	virtual string toString();
};


#endif  //_CHAT_MESSAGE_H
