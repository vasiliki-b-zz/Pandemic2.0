#include <iostream>

#include "Game.h"

using namespace std;

int main()
{
	cout << "********************************************************************************" << endl;
	cout << "** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **" << endl;
	cout << "* * * * * * * * * * * * * * COMP 345 - Assignment #1 * * * * * * * * * * * * * *" << endl;
	cout << "* * * * * * * * * * * * * * * PANDEMIC BOARD GAME  * * * * * * * * * * * * * * *" << endl;
	cout << "** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **" << endl;
	cout << "********************************************************************************" << endl;
	
	Game game = Game();
	std::string input;

	cout << "Welcome to Pandemic!\n" << endl;

	game.run();

	system("PAUSE");
}