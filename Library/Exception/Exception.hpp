#ifndef EXCEPTION
#define EXCEPTION

#include<iostream>
#include<string>

using namespace std;

class Exception{
	protected : 
		string _head;
		string _message;
	public :
		Exception();
		Exception(const char * m); 
		string getMessage(){return _message;}
		string getHeader(){return _head;}
		void setHeader(const char * h){_head = h;}
		void setMessage(const char * m){_message = m;}
		void display();
};

class ConnectionException : public Exception{
	public :
		ConnectionException(){_head = "ConnectionException";}
        ConnectionException(const char * c) : Exception(c){}
};

class IndexOutOfBoundException : public Exception{
	public :
		IndexOutOfBoundException(){_head = "IndexOutOfBoundException";}
		IndexOutOfBoundException(const char * c) : Exception(c){}
};

class InteruptedException :public Exception{
	public :
		InteruptedException(){_head = "InteruptedException";}
		InteruptedException(const char * c) : Exception(c){}
};

class EndOfGameException : public Exception{
	public :
		EndOfGameException(){_head = "EndOfGameException";}
		EndOfGameException(const char * c) : Exception(c){}
};
#endif
