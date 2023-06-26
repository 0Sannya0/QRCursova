	#include <iostream>
#include <string>
#include "chess.h"

using namespace std;





int main()
{
	// Створення об'єкта класу Board
	
	Board b;
	string s;
	bool newgame = true;
	cout << "   _____ _    _ ______  _____ _____ \n  / ____| |  | |  ____|/ ____/ ____| \n | |    | |__| | |__  | (___| (___  \n | |    |  __  |  __|  \\___  \\___ \\ \n | |____| |  | | |____ ____) |___) | \n  \\_____|_|  |_|______|_____/_____/ \n" << endl;
	
	cout << "Введіть ключ, щоб пройти" << endl;
	cin >> s;

	while(newgame){
		
		// Виклик функції setBoard() для ініціалізації дошки
		
		b.setBoard();
		
		// Виклик функції playGame() для гри, поки гра триває
		
		while (b.playGame());
		cout << "Зіграти ще раз? (Так, щоб погодитись все інше - відмовитись) ";
		cin >> s;
		if (s != "y")
			newgame = false;
	}


	return 0;
}