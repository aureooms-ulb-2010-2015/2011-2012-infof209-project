#if !defined(_FEED_H)
#define _FEED_H
#include <string>
#include <map>
using namespace std;

class Feed{

private:
	string __type;
	string __author;
	string __content;
	long int __timestamp;

public:
	virtual string toString()=0;

	virtual string type();
	virtual Feed& type(string type);
	virtual string author();
	virtual Feed& author(string author);
	virtual string content();
	virtual Feed& content(string content);
	virtual long int timestamp();
	virtual Feed& timestamp(long int timestamp);

	virtual string time();
	virtual string serialize();
	virtual map<string,string> deserialize(string encoded);

};


#endif
