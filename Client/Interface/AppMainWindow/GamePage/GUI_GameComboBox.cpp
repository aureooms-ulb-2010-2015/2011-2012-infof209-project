#include "GUI_GameComboBox.hpp"

GUI_GameComboBox::GUI_GameComboBox(QWidget* parent) : QComboBox(parent){
	this->addItem("Backgammon");
	this->addItem("Dames");
	this->addItem("Ludo");
	this->addItem("Reversi");
}
