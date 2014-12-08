#include<unistd.h>
#include <iostream>
#include<pthread.h>
#include "Thread.hpp"
#include "../Exception/Exception.hpp"

#define TIMEOUT 1

using namespace std;

/*
____________________________________________________________________________________

Constructeurs
____________________________________________________________________________________

*/

Thread::Thread(void * arg){
	this->setArg(arg);
	this->setState('n');
}

Thread::Thread(){
	this->setState('n');
}

/*
____________________________________________________________________________________

Méthodes principales
____________________________________________________________________________________

*/

int Thread::start(){
	this->setState('r');
	int code = pthread_create(this->getThread(), NULL, threadFunction, (void *)this);
	return code;
}

void Thread::wait(){
	this->setState('w');
	while(true){
		sleep(TIMEOUT);
		if(this->getState() == 'r'){
			throw new InteruptedException();
		}
	}
}

void Thread::wakeUp(){
	this->setState('r');
}

void Thread::wakeUp(Thread * t){
	t->wakeUp();
}

/*
____________________________________________________________________________________

Getters
____________________________________________________________________________________

*/

void * Thread::getArg(){
	return this->_arg;
}

pthread_t * Thread::getThread(){
	return &this->_thread;
}

unsigned char Thread::getState(){
	return this->_state;
}

/*
____________________________________________________________________________________

Setters
____________________________________________________________________________________

*/

void Thread::setArg(void * arg){
	this->_arg=arg;
}

void Thread::setState(unsigned char c){
	this->_state=c;
}

/*
____________________________________________________________________________________

Méthodes statiques
____________________________________________________________________________________

*/

void * Thread::threadFunction(void * thread){
	Thread * threadPt = (Thread *)thread;
	void * res = threadPt->run(threadPt->getArg());
	return res;
}
