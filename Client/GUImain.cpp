#include "GameServerUI.hpp"
#include <QApplication>
#include <QTextCodec>
#include <QRect>
#include "./Interface/LoginPage/LoginPage.hpp"
#include <string>

using namespace std;

int main(int argc, char *argv[]){
	QApplication app(argc, argv);

	GameServerUI* gameserv = NULL;
	QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));

    LoginPage* login = new LoginPage(gameserv);
/*
    const int width = QApplication::desktop()->width();
    const int height = QApplication::desktop()->height();
    const QRect rect = QApplication::desktop()->rect();
    
    const int left = rect.left();
    const int right = rect.right();
    const int bottom = rect.bottom();
    const int top = rect.top();

	app.setGeometry((width-app.Geometry.width())/2,(height-app.Geometry.height())/2,app.Geometry.width(),app.Geometry.height());
*/
    login->show();
   
    return app.exec();
}
