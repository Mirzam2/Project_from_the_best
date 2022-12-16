#include "casino.h"
using namespace std;

int Dices::RollofDice()
{
	int dicevalue;
	dicevalue = rand() % 6 + 1;
	return dicevalue;
}

void Dices::initplayerpoints(int a)
{
	playerpoints = new int[a];
	for (int i = 0; i < a; i++)
	{
		playerpoints[i] = 0;
	}
}

void Dices::setpoints(int a)
{
	initplayerpoints(a);
	srand(time(0));
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < a; j++)
		{
			playerpoints[j] += RollofDice();
		}
	}
}

void Dices::coutpoints(int index)
{
	cout << "summ of points = " << playerpoints[index] << endl;
}

int Dices::getpoints(int a)
{
	return playerpoints[a];
}

void Dices::setmaxpoints(int a)
{
	maxpoints = playerpoints[0];
	for (int i = 0; i < a; i++)
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
	int *gamecontinue = new int;
	for (int i = 0; i < numofplayers; i++)
	{
		cout << Players[i].GetName() << ' ';
		Players[i].SetintBank();
		f << Players[i].GetName() << ' ';
	}
	f << endl;

	for (int i = 0; i < numofplayers; i++)
	{
		f << Players[i].getbank() << ',';
	}
	f << endl;

	do
	{

		for (int i = 0; i < numofplayers; i++)
		{
			cout << Players[i].GetName() << ' ';
			Players[i].SetBet();
		}
		std::cout << "number ff: " << numofplayers << '\n';
		if (Dices::isequal() == false)
		{
			while (Dices::isequal() == false)
			{
				cout << "For this game all bets must be equal, enter correct bets" << endl;
				for (int i = 0; i < numofplayers; i++)
				{
					cout << Players[i].GetName() << ' ';
					Players[i].SetBet();
				}
			}
		}
		// Игроки делают ставки

		for (int i = 0; i < numofplayers; i++)
		{
			cout << Players[i].GetName() << ' ';
			Players[i].setcurrbank();
		}
		// Показывает столько у кого сколько денег осталось

		for (int i = 0; i < numofplayers; i++)
		{
			Players[i].setsummarybet(Players[i].getbet());
		}
		// Считает суммарную ставку

		Croupier.BidsCollect(numofplayers * Players[0].getbet());
		// Крупье собирает деньги
		setpoints(numofplayers); // игроки бросают кубики

		for (int i = 0; i < numofplayers; i++)
		{
			cout << Players[i].GetName() << endl;
			coutpoints(i);
			cout << endl;
		}
		// Вывод у кого сколько выпало

		setmaxpoints(numofplayers);
		int numofwinners = 0;

		for (int i = 0; i < numofplayers; i++)
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

		for (int i = 0; i < numofplayers; i++)
		{
			if (Players[i].getwin() == 1)
			{
				Players[i].SetPrize(Croupier.Giveprize() / numofwinners);
				cout << Players[i].GetName() << " is win" << endl;
				cout << "summ of prize " << Players[i].getprize() << endl;
			}
			else
				Players[i].SetPrize(0);
		} // раздают победителям деньги

		numofwinners = 0;

		for (int i = 0; i < numofplayers; i++)
		{
			cout << Players[i].GetName() << ' ';
			Players[i].SetoutBank();
		}

		for (int i = 0; i < numofplayers; i++)
		{
			Players[i].setwin(0);
		}

		for (int i = 0; i < numofplayers; i++)
		{
			f << Players[i].getbank() << ',';
		}
		f << endl;

		isbankrupt();

		cout << endl;
		cout << "do you want to play again ? " << endl;
		cout << "1) yes " << endl;
		cout << "2) no " << endl;

		cin >> *gamecontinue;
	} while (*gamecontinue != 2 && isbankrupt() == false);

	for (int i = 0; i < numofplayers; i++)
	{
		cout << Players[i].GetName() << ':' << endl;
		cout << "summary bet = " << Players[i].getsummarybet() << endl;
		cout << "summary prize = " << Players[i].getsummaryprize() << endl;
	}

	f.close();
	delete gamecontinue;
}

/*void Dices::gameprocess() {
	srand(time(0));

	for (int i = 0; i < 2; i++) {

		playerpoints += playerdicesvalues[i];
	}

	for (int i = 0; i < 2; i++) {
		computerdicevalues[i] = RollofDice();
		computerpoints += computerdicevalues[i];
	}

	/*cout << "Summ of player points = " << playerpoints << endl;
	cout << "There are player's points" << endl;*/

/*for (int i = 0; i < 2; i++) {
	switch (playerdicesvalues[i]) {
	case 1:
		cout << "-----------" << endl;
		cout << "|         |" << endl;
		cout << "|    0    |" << endl;
		cout << "|         |" << endl;
		cout << "-----------" << endl;
		break;

	case 2:
		cout << "-----------" << endl;
		cout << "|    0    |" << endl;
		cout << "|         |" << endl;
		cout << "|    0    |" << endl;
		cout << "-----------" << endl;
		break;

	case 3:
		cout << "-----------" << endl;
		cout << "|  0      |" << endl;
		cout << "|    0    |" << endl;
		cout << "|      0  |" << endl;
		cout << "-----------" << endl;
		break;

	case 4:
		cout << "-----------" << endl;
		cout << "|  0   0  |" << endl;
		cout << "|         |" << endl;
		cout << "|  0   0  |" << endl;
		cout << "-----------" << endl;
		break;

	case 5:
		cout << "-----------" << endl;
		cout << "|  0   0  |" << endl;
		cout << "|    0    |" << endl;
		cout << "|  0   0  |" << endl;
		cout << "-----------" << endl;
		break;

	case 6:
		cout << "-----------" << endl;
		cout << "|  0   0  |" << endl;
		cout << "|  0   0  |" << endl;
		cout << "|  0   0  |" << endl;
		cout << "-----------" << endl;
		break;
	}
}


cout << "Summ of computer points = " << computerpoints << endl;
cout << "There are computer's points" << endl;

for (int i = 0; i < 2; i++) {
	switch (computerdicevalues[i]) {
	case 1:
		cout << "-----------" << endl;
		cout << "|         |" << endl;
		cout << "|    0    |" << endl;
		cout << "|         |" << endl;
		cout << "-----------" << endl;
		break;

	case 2:
		cout << "-----------" << endl;
		cout << "|    0    |" << endl;
		cout << "|         |" << endl;
		cout << "|    0    |" << endl;
		cout << "-----------" << endl;
		break;

	case 3:
		cout << "-----------" << endl;
		cout << "|  0      |" << endl;
		cout << "|    0    |" << endl;
		cout << "|      0  |" << endl;
		cout << "-----------" << endl;
		break;

	case 4:
		cout << "-----------" << endl;
		cout << "|  0   0  |" << endl;
		cout << "|         |" << endl;
		cout << "|  0   0  |" << endl;
		cout << "-----------" << endl;
		break;

	case 5:
		cout << "-----------" << endl;
		cout << "|  0   0  |" << endl;
		cout << "|    0    |" << endl;
		cout << "|  0   0  |" << endl;
		cout << "-----------" << endl;
		break;

	case 6:
		cout << "-----------" << endl;
		cout << "|  0   0  |" << endl;
		cout << "|  0   0  |" << endl;
		cout << "|  0   0  |" << endl;
		cout << "-----------" << endl;
		break;
	}
}
*/

/*if (playerpoints > computerpoints) {
	prizesumm = bet * 2;
	cout << "You win, your prize summ = " << prizesumm << endl;
}

else if (playerpoints < computerpoints) {
	prizesumm = 0;
	cout << "You loose" << endl;
}

else {
	prizesumm = bet;
	cout << "tie" << endl;
}

playerpoints = 0;
computerpoints = 0;

SetoutBank();

*/
