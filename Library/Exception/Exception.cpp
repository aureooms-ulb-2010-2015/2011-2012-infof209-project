#include "Exception.hpp"
#include <iostream>

using namespace std;

/*
____________________________________________________________________________________

Constructeurs
____________________________________________________________________________________

*/

Exception::Exception():_head("Undefined Exception"){}
Exception::Exception(const char * m):_head("Undefined Exception") {
    _message = m;
}

/*
____________________________________________________________________________________

Autres méthodes non classables
____________________________________________________________________________________

*/

void Exception::display(){
    cout<<"A "<<this->getHeader()<<" has been throwed :\n\t"<<this->getMessage()<<endl;
}
