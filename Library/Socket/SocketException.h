// SocketException class


#ifndef SocketException_class
#define SocketException_class

#include <string>

class SocketException{
	private:
		std::string __description;

	public:
		SocketException(){};
		SocketException(std::string description):__description(description){};
		~SocketException(){};
 		std::string description() { return this->__description; }




};

class SocketCreationException : public SocketException{
	public:
		SocketCreationException(){
			SocketException("Could not create socket.");
		}
};

class SocketListenException : public SocketException{
	public:
		SocketListenException(){
			SocketException("Could not listen to socket.");
		}
};

class SocketAcceptException : public SocketException{
	public:
		SocketAcceptException(){
			SocketException("Could not accept socket.");
		}
};

class SocketBindException : public SocketException{
	public:
		SocketBindException(){
			SocketException("Could not bind to port.");
		}
};
class SocketWriteException : public SocketException{
	public:
		SocketWriteException(){
			SocketException("Could not write to socket.");
		}
};
class SocketReadException : public SocketException{
	public:
		SocketReadException(){
			SocketException("Could not read from socket.");
		}
};

#endif
