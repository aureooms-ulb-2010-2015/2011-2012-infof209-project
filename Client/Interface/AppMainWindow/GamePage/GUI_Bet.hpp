#ifndef DEF_BET
#define DEF_BET

#include <QDialog>
#include <QMessageBox>
#include <QSpinBox>
#include <QLabel>
#include <QGridLayout>
#include <QPushButton>
#include <QListWidget>
#include <sstream>

#include "../../../Bet/Bet.hpp"
#include "../../ErrorBox/ErrorBox.hpp"
#include "../../../../Common/Request.hpp"
#include "../../../GameServerUI.hpp"

class GUI_Bet : public QDialog, public Bet {
	Q_OBJECT
private:

	GameServerUI* _gameServ;
	
	QVBoxLayout* _globalLayout;
	
	/* display Mess */
	QMessageBox* _message;
	
	/* ASK */
   	QDialog* _askWidget;
   	QVBoxLayout* _askLayout;
   	QLabel* _askText;
   	QSpinBox* _askSpinBox;
   	QPushButton* _confirmBet;
	
	/* Display Bets */
	QDialog* _dispWidget;
	QGridLayout* _dispLayout;
	QLabel* _dispText;
	QListWidget* _dispBets;
	QPushButton* _validBets;
	QPushButton* _cancelBets;
   	
public:
	virtual void displayWait(bool);
	virtual void displayValid(bool);
	virtual void displayNotValid(bool);
	virtual void displayBets();
	
	virtual void route(Request *);
	virtual void addBetToList(Request*);

	GUI_Bet(GameServerUI* gameServ);
	
public slots:
	void s_askAmount();
	void s_askValidation();
	
	void s_confirmBet();
	void s_validBets();
	void s_cancelBets();
		
signals:
	void si_askAmount();
	void si_askValidation();
	void si_mustUpdate();
};
#endif
