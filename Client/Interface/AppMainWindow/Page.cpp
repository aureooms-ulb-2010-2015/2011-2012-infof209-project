#include "Page.hpp"

Page::Page(string Nickname, GameServerUI* GameServ){
	_nickname = Nickname;
	_gameServ = GameServ;
}

Page::~Page(){
}

string Page::getNickname(){
	return _nickname;
}
