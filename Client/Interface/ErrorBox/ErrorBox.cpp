#include "ErrorBox.hpp"	

using namespace std;

ErrorBox::ErrorBox(string Title, string Text){
		_errorMessage = new QMessageBox(this);
		_errorMessage->setWindowTitle(QString(Title.c_str()));
		_errorMessage->setText(QString(Text.c_str()));
		_errorMessage->show();
}
