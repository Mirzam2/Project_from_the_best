#include "casino.h"

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
	std::cin >> numofplayers;
	Players = std::make_unique<Player[]>(numofplayers);
}

int Casino::Getnumofplayers()
{
	return numofplayers;
}

void Casino::Initplayers()
{
	for (int i = 0; i < numofplayers; ++i)
	{
		std::cout << "Enter name of " << i + 1 << " player" << '\n';
		Players[i].SetName();
	}
}

void Casino::game()
{

	int gamenumber;
	std::cout << "Enter num of players" << '\n';
	Setnumofplayers();
	Initplayers();

	std::cout << "there are list of our games, which you want to play ?" << '\n'; // Выбор игры, можно в отдельное место
	std::cout << "1) dices" << '\n';
	std::cout << "2) roulete" << '\n';
	std::cout << "3) BlackJack" << '\n';
	std::cin >> gamenumber;

	if (gamenumber != 1 && gamenumber != 2 && gamenumber != 3)
	{ // проверка на то что выбрал правильно
		std::cout << "choose correct number of game" << '\n';
		std::cin >> gamenumber;
	}
	Croupier.SetName();
	std::cout << "your croupier is " << Croupier.GetName() << '\n';
	if (gamenumber == 1)
	{

		Dices play(std::move(Players), Croupier, numofplayers);
		play.game_process();
	}
	else if (gamenumber == 2)
	{

		Roulete play(std::move(Players), Croupier, numofplayers);
		play.game_process(Casinobank);
	}
	else
	{
		BlackJack play(std::move(Players), Croupier, numofplayers);
		play.game_process();
	}
}
