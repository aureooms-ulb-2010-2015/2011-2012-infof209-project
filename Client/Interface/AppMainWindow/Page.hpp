#ifndef DEF_PAGE
#define DEF_PAGE

#include <QWidget>

#include "../../GameServerUI.hpp"

class Page : public QWidget{
protected:
	string _nickname;
	GameServerUI * _gameServ;

public:
	string getNickname();
	Page(string Nickname, GameServerUI* GameServ);
	virtual ~Page() = 0;
};
#endif
