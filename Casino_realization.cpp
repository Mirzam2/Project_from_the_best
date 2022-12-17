#include "casino.h"
using namespace std;

string coutblack(bool isblack)
{
	string black;
	if (isblack == true)
	{
		black = "black";
	}
	else
		black = "red";
	return black;
}

string couteven(bool iseven)
{
	string chet;
	if (iseven == true)
	{
		chet = "even";
	}
	else
		chet = "not even";
	return chet;
}

void Casino::Setnumofplayers()
{
	cin >> numofplayers;
	Players = new Player[numofplayers];
}

int Casino::Getnumofplayers()
{
	return numofplayers;
}

void Casino::Initplayers()
{
	for (int i = 0; i < numofplayers; i++)
	{
		cout << "Enter name of " << i + 1 << " player" << endl;
		Players[i].SetName();
	}
}

void Casino::game()
{

	int gamenumber;
	cout << "Enter num of players" << endl;
	Setnumofplayers();
	Initplayers();

	cout << "there are list of our games, which you want to play ?" << endl; // Выбор игры, можно в отдельное место
	cout << "1) dices" << endl;
	cout << "2) roulete" << endl;
	cout << "3) BlackJack" << endl;
	cin >> gamenumber;

	if (gamenumber != 1 && gamenumber != 2 && gamenumber != 3)
	{ // проверка на то что выбрал правильно
		cout << "choose correct number of game" << endl;
		cin >> gamenumber;
	}
	Croupier.SetName();
	cout << "your croupier is " << Croupier.GetName() << endl;
	if (gamenumber == 1)
	{

		Dices play(Players, Croupier, numofplayers);
		play.game_process();
	}
	else if (gamenumber == 2)
	{

		Roulete play(Players, Croupier, numofplayers);
		play.game_process(Casinobank);
	}
	else
	{
		BlackJack play(Players, Croupier, numofplayers);
		play.game_process();
	}
}
