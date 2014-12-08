
#include <stdlib.h>
#include <iostream>
using namespace std;

int main(){
	
	cout << "Quel Tuto? (1 = Dames, 2=Ludo, 3= Backgammon, 4=Reversi"<<endl;
	int choice;
	cin >> choice;
	if(choice == 1)
		system("less DamesTuto.txt");
	if(choice == 2)
		system("less LudoTuto.txt");
	if(choice == 3)
		system("less BackgammonTuto.txt");
	if(choice == 4)
		system("less ReversiTuto.txt");

	return 0;
}