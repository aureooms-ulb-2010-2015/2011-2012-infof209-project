#ifndef DEF_GUI_CREATEGAMEPOPUP
#define DEF_GUI_CREATEGAMEPOPUP

#include <QDialog>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QLineEdit>
#include <string>
#include "GUI_GameComboBox.hpp"

using namespace std;


class GUI_CreateGamePopUp : public QDialog{
	Q_OBJECT
private:
   	QGridLayout* _cg_layout;
   	QLabel* _cg_text;
   	
   	QPushButton* _cg_buttonCreate;
   	QLabel* _cg_typeGame;
   	QLabel* _cg_nbPlayers;
   	QLabel* _cg_gameName;
   	
   	GUI_GameComboBox* _cg_typeGameBox;
   	QComboBox* _cg_nbPlayersBox;
   	QLineEdit* _cg_gameNameEdit;

public:
	QPushButton* getCg_buttonCreate();
	GUI_GameComboBox* getCg_typeGameBox();
	QComboBox* getCg_nbPlayersBox();
	QLineEdit* getCg_gameNameEdit();
	
	GUI_CreateGamePopUp(string name);
	
public slots:
	void s_ModifyNbPlayers(QString index);
};
#endif
