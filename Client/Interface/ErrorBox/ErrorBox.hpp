#ifndef DEF_ERRORBOX
#define DEF_ERRORBOX
#include <QMessageBox>
#include <string>

using namespace std;

class ErrorBox : public QMessageBox{		
private:
	QMessageBox* _errorMessage;
public:
	ErrorBox(string Title, string Text);
};
#endif
