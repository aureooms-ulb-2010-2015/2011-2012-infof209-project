#if !defined(_CHAT_NOTIFICATION_H)
#define _CHAT_NOTIFICATION_H

#include "Feed.h"

using namespace std;

class Chat_notification : public Feed{
public:
	Chat_notification(string author,string content);
	Chat_notification(string encoded);
	virtual string toString();
};


#endif
