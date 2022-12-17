#include "casino.h";
using namespace std;
Roulete::Roulete() : Game() {}
Roulete::Roulete(Player *Players, Host Croupier, int numofplayers) : Game(Players, Croupier, numofplayers)
{
	std::cout << "Game Roulete start \n Number players: " << numofplayers << "\n";
}
void Roulete::initplayervalues(int n)
{
	playervalues = new rouletevalue[n];
}

void Roulete::setplayervalnum(int index, int a)
{
	playervalues[index].value = a;
}

void Roulete::setplayervalisblack(int index, bool color)
{
	playervalues[index].isblack = color;
}

void Roulete::setplayervaliseven(int index, bool even)
{
	playervalues[index].isblack = even;
}

void Roulete::setplayervaliszero(int index, bool zero)
{
	playervalues[index].iszero = zero;
}

void Roulete::setplayerbet(int index, stavka stavka)
{
	playervalues[index].playerbet = stavka;
}

int Roulete::getplayervalnum(int index)
{
	return playervalues[index].value;
}

bool Roulete::getplayervalisblack(int index)
{
	return playervalues[index].isblack;
}

bool Roulete::getplayervaliseven(int index)
{
	return playervalues[index].iseven;
}

bool Roulete::getplayervaliszero(int index)
{
	return playervalues[index].iszero;
}

stavka Roulete::getplayerstavka(int index)
{
	return playervalues[index].playerbet;
}

void Roulete::RollofRoulete()
{
	srand(time(0));

	int *blacknums = new int[18]{2, 4, 6, 8, 10, 11, 13, 15, 17, 20, 22, 24, 26, 28, 29, 31, 33, 35};

	computerval.value = rand() % 37;

	if (computerval.value == 0)
	{
		computerval.iszero = 1;
	}
	else
	{
		computerval.iszero = 0;
		if (computerval.value % 2 == 0)
		{
			computerval.iseven = 1;
		}
		else
			computerval.iseven = 0;
	}

	int *numblack = new int;
	*numblack = 0;

	for (int i = 0; i < 18; i++)
	{
		if (computerval.value == blacknums[i])
		{
			(*numblack)++;
			break;
		}
	}

	if (*numblack != 0)
	{
		computerval.isblack = true;
	}
	else
		computerval.isblack = false;

	delete numblack;
	delete[] blacknums;
}

int Roulete::getcompnum()
{
	return computerval.value;
}

bool Roulete::getcompblack()
{
	return computerval.isblack;
}

bool Roulete::getcompeven()
{
	return computerval.iseven;
}

bool Roulete::getcompzero()
{
	return computerval.iszero;
}
void Roulete::game_process(int &Casinobank)
{
	bool gamecontinue = true;
	for (int i = 0; i < numofplayers; i++)
	{
		cout << Players[i].GetName() << ' ';
		Players[i].SetintBank();
	}

	initplayervalues(numofplayers);

	do
	{
		for (int i = 0; i < numofplayers; i++)
		{
			int n;
			cout << Players[i].GetName() << " what do you want to bet ?" << endl;
			cout << "1) color " << endl;
			cout << "2) number" << endl;
			cout << "3) range " << endl;
			cout << "4) even/not even " << endl;
			cin >> n;

			if (n == 1)
			{
				setplayerbet(i, color);

				int colornum;
				cout << "what color do you want to make a bet ?" << endl;
				cout << "1) Red" << endl;
				cout << "2) Black " << endl;
				cin >> colornum;

				if (colornum != 1 && colornum != 2)
				{
					while (colornum != 1 && colornum != 2)
					{
						cout << "choose correct number of color";
						cin >> colornum;
					}
				}

				if (colornum == 1)
				{
					setplayervalisblack(i, false);
				}
				else
					setplayervalisblack(i, true);

				Players[i].SetBet();
				Players[i].setsummarybet(Players[i].getbet());
				Casinobank += Players[i].getbet();
				Players[i].setcurrbank();
			}

			else if (n == 2)
			{
				setplayerbet(i, number);

				int number;
				cout << "what number do you want to bet on ?" << endl;
				cin >> number;
				if (number > 36 || number < 0)
				{
					while (number > 36 || number < 0)
					{
						cout << "the number you want to bet on should be in the range from 0 to 36, choose another number." << endl;
						cin >> number;
					}
				}

				setplayervalnum(i, number);
				if (number == 0)
				{
					setplayervaliszero(i, true);
				}
				else
					setplayervaliszero(i, false);

				Players[i].SetBet();
				Players[i].setsummarybet(Players[i].getbet());
				Casinobank += Players[i].getbet();
				Players[i].setcurrbank();
			}

			else if (n == 3)
			{
				setplayerbet(i, range);

				int rangenumber;
				cout << "what range do you want to bet on ?" << endl;
				cout << "1) 0 - 17 " << endl;
				cout << "2) 18 - 36 " << endl;
				cin >> rangenumber;

				if (rangenumber != 1 && rangenumber != 2)
				{
					while (rangenumber != 1 && rangenumber != 2)
					{
						cout << "enter correct number of range" << endl;
						cin >> rangenumber;
					}
				}

				if (rangenumber == 1)
				{
					setplayervalnum(i, 17);
				}
				else
					setplayervalnum(i, 18);

				Players[i].SetBet();
				Players[i].setsummarybet(Players[i].getbet());
				Casinobank += Players[i].getbet();
				Players[i].setcurrbank();
			}

			else
			{
				setplayerbet(i, even);

				int evennum;
				cout << "what do you want to bet on ?" << endl;
				cout << "1) not even" << endl;
				cout << "2) is even" << endl;
				cin >> evennum;

				if (evennum != 1 && evennum != 2)
				{
					while (evennum != 1 && evennum != 2)
					{
						cout << "choose correct number of your bet" << endl;
						cin >> evennum;
					}
				}

				if (evennum == 1)
				{
					setplayervaliseven(i, false);
				}
				else
					setplayervaliseven(i, true);

				Players[i].SetBet();
				Players[i].setsummarybet(Players[i].getbet());
				Casinobank += Players[i].getbet();
				Players[i].setcurrbank();
			}
		}

		RollofRoulete();

		for (int i = 0; i < numofplayers; i++)
		{

			if (getplayerstavka(i) == color)
			{
				if (getplayervalisblack(i) == getcompblack())
				{
					Players[i].SetPrize(2 * Players[i].getbet());
					Casinobank -= Players[i].getcurrprize();
					cout << Players[i].GetName() << " ,you win, your prizesumm " << Players[i].getcurrprize() << endl;
					Players[i].SetoutBank();
				}
				else
				{
					Players[i].SetPrize(0);
					Casinobank -= Players[i].getcurrprize();
					cout << Players[i].GetName() << " you loose" << endl;
					Players[i].SetoutBank();
				}
			}

			else if (getplayerstavka(i) == number)
			{
				if (getplayervalnum(i) == getcompnum())
				{
					Players[i].SetPrize(37 * Players[i].getbet());
					Casinobank -= Players[i].getcurrprize();
					cout << Players[i].GetName() << " ,you win, your prizesumm " << Players[i].getcurrprize() << endl;
					Players[i].SetoutBank();
				}
				else
				{
					Players[i].SetPrize(0);
					Casinobank -= Players[i].getcurrprize();
					cout << Players[i].GetName() << " you loose" << endl;
					Players[i].SetoutBank();
				}
			}

			else if (getplayerstavka(i) == even)
			{
				if (getplayervaliseven(i) == getcompeven() && getcompzero() == false)
				{
					Players[i].SetPrize(2 * Players[i].getbet());
					Casinobank -= Players[i].getcurrprize();
					cout << Players[i].GetName() << " ,you win, your prizesumm " << Players[i].getcurrprize() << endl;
					Players[i].SetoutBank();
				}
				else
				{
					Players[i].SetPrize(0);
					Casinobank -= Players[i].getcurrprize();
					cout << Players[i].GetName() << " you loose" << endl;
					Players[i].SetoutBank();
				}
			}
			else if (getplayerstavka(i) == range)
			{
				if (getplayervalnum(i) == 17 && getplayervalnum(i) >= getcompnum())
				{
					Players[i].SetPrize(2 * Players[i].getbet());
					Casinobank -= Players[i].getcurrprize();
					cout << Players[i].GetName() << " ,you win, your prizesumm " << Players[i].getcurrprize() << endl;
					Players[i].SetoutBank();
				}
				else if (getplayervalnum(i) == 18 && getplayervalnum(i) <= getcompnum())
				{
					Players[i].SetPrize(2 * Players[i].getbet());
					Casinobank -= Players[i].getcurrprize();
					cout << Players[i].GetName() << " ,you win, your prizesumm " << Players[i].getcurrprize() << endl;
					Players[i].SetoutBank();
				}
				else
				{
					Players[i].SetPrize(0);
					Casinobank -= Players[i].getcurrprize();
					cout << Players[i].GetName() << " you loose" << endl;
					Players[i].SetoutBank();
				}
			}
		}

		isbankrupt();

		cout << endl;
		cout << "do you want to play again ? " << endl;
		cout << "1) Yes " << endl;
		cout << "0) No " << endl;

		cin >> gamecontinue;
	} while (gamecontinue && isbankrupt() != true && Casinobank > 0);

	for (int i = 0; i < numofplayers; i++)
	{
		cout << Players[i].GetName() << ':' << endl;
		cout << "summary bet = " << Players[i].getsummarybet() << endl;
		cout << "summary prize = " << Players[i].getsummaryprize() << endl;
	}
}