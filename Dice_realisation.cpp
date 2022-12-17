#include "casino.h"
Dices::Dices() : Game(){}; // конструктор по умолчанию
Dices::Dices(std::unique_ptr<Player[]> Players, Host Croupier, int numofplayers) : Game(std::move(Players), Croupier, numofplayers)
{
	std::cout << "Game Dices start \n Number players: " << numofplayers << "\n";
}

int Dices::RollofDice()
{
	int dicevalue;
	dicevalue = rand() % 6 + 1;
	return dicevalue;
}

void Dices::initplayerpoints(int a)
{
	playerpoints = std::make_unique<int[]>(numofplayers);;
	for (int i = 0; i < a; ++i)
	{
		playerpoints[i] = 0;
	}
}

void Dices::setpoints(int a)
{
	initplayerpoints(a);
	srand(time(0));
	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < a; j++)
		{
			playerpoints[j] += RollofDice();
		}
	}
}

void Dices::coutpoints(int index)
{
	cout << "summ of points = " << playerpoints[index] << '\n';
}

int Dices::getpoints(int a)
{
	return playerpoints[a];
}

void Dices::setmaxpoints(int a)
{
	maxpoints = playerpoints[0];
	for (int i = 0; i < a; ++i)
	{
		if (playerpoints[i] > maxpoints)
		{
			maxpoints = playerpoints[i];
		}
	}
}

int Dices::getmaxpoints()
{
	return maxpoints;
}

void Dices::game_process()
{
	bool gamecontinue = true;
	for (int i = 0; i < numofplayers; ++i)
	{
		cout << Players[i].GetName() << ' ';
		Players[i].SetintBank();
	}

	do
	{

		for (int i = 0; i < numofplayers; ++i)
		{
			cout << Players[i].GetName() << ' ';
			Players[i].SetBet();
		}
		if (isequal() == false)
		{
			while (isequal() == false)
			{
				cout << "For this game all bets must be equal, enter correct bets" << '\n';
				for (int i = 0; i < numofplayers; ++i)
				{
					cout << Players[i].GetName() << ' ';
					Players[i].SetBet();
				}
			}
		}
		// Игроки делают ставки

		for (int i = 0; i < numofplayers; ++i)
		{
			cout << Players[i].GetName() << ' ';
			Players[i].setcurrbank();
		}
		// Показывает столько у кого сколько денег осталось

		for (int i = 0; i < numofplayers; ++i)
		{
			Players[i].setsummarybet(Players[i].getbet());
		}
		// Считает суммарную ставку

		Croupier.BidsCollect(numofplayers * Players[0].getbet());
		// Крупье собирает деньги
		setpoints(numofplayers); // игроки бросают кубики

		for (int i = 0; i < numofplayers; ++i)
		{
			std::cout << Players[i].GetName() << '\n';
			coutpoints(i);
			std::cout << '\n';
		}
		// Вывод у кого сколько выпало

		setmaxpoints(numofplayers);
		int numofwinners = 0;

		for (int i = 0; i < numofplayers; ++i)
		{
			if (getpoints(i) == getmaxpoints())
			{
				Players[i].setwin(1);
				numofwinners++;
			}
			else
				Players[i].setwin(0);
		}
		// определяем победителей

		for (int i = 0; i < numofplayers; ++i)
		{
			if (Players[i].getwin() == 1)
			{
				Players[i].SetPrize(Croupier.Giveprize() / numofwinners);
				std::cout << Players[i].GetName() << " is win" << '\n';
				std::cout << "summ of prize " << Players[i].getprize() << '\n';
			}
			else
				Players[i].SetPrize(0);
		} // выводим это
		for (int i = 0; i < numofplayers; ++i)
		{
			std::cout << Players[i].GetName() << ' ';
			Players[i].SetoutBank();
		}
		std::cout << '\n';
		std::cout << "Do you want to play again? " << '\n';
		std::cout << "0) No " << '\n';
		std::cout << "1) Yes " << '\n';
		std::cin >> gamecontinue;
	} while (gamecontinue && isbankrupt() == false);

	for (int i = 0; i < numofplayers; ++i)
	{
		std::cout << Players[i].GetName() << ':' << '\n';
		std::cout << "summary bet = " << Players[i].getsummarybet() << '\n';
		std::cout << "summary prize = " << Players[i].getsummaryprize() << '\n';
	} // вывод конечного результата
}
