#ifndef THREAD
#define THREAD

#include<pthread.h>
#include <sys/types.h>

/*
Thread states are :
	-'w' : waiting
	-'r' : running
	-'n' : not running
*/

class Thread{
	private :
		void * _arg;
		pthread_t _thread;
		unsigned char _state;
	public :
		Thread(void *);
		Thread();
		virtual int start();
		virtual void * run(void *)=0;
		virtual void wait();
		virtual void wakeUp();
		virtual void wakeUp(Thread *);
		virtual void setArg(void *);
		virtual void * getArg();
		virtual unsigned char getState();
		virtual void setState(unsigned char);
		virtual pthread_t * getThread();
		static void * threadFunction(void *);
};
#endif
