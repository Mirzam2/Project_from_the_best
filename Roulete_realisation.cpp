#include "casino.h";
Roulete::Roulete() : Game() {}
Roulete::Roulete(Player *Players, Host Croupier, int numofplayers) : Game(Players, Croupier, numofplayers)
{
	std::cout << "Game Roulete start \n Number players: " << numofplayers << "\n";
}
void Roulete::initplayervalues()
{
	playervalues = new rouletevalue[numofplayers];
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
	std::cout << "A number fell on the roulette wheel: " << computerval.value << '\n';
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

	for (int i = 0; i < 18; ++i)
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
void Roulete::lose(int index, int &Casinobank)
{
	Players[index].SetPrize(0);
	Casinobank -= Players[index].getcurrprize();
	std::cout << Players[index].GetName() << " you loose" << '\n';
	Players[index].SetoutBank();
};
void Roulete::win(int index, int &Casinobank, int multy)
{
	Players[index].SetPrize(multy * Players[index].getbet());
	Casinobank -= Players[index].getcurrprize();
	std::cout << Players[index].GetName() << " ,you win, your prizesumm " << Players[index].getcurrprize() << '\n';
	Players[index].SetoutBank();
};
void Roulete::game_process(int &Casinobank)
{
	bool gamecontinue = true;
	for (int i = 0; i < numofplayers; ++i)
	{
		cout << Players[i].GetName() << ' ';
		Players[i].SetintBank();
	}

	initplayervalues();

	do
	{
		for (int i = 0; i < numofplayers; ++i)
		{
			int n;
			std::cout << Players[i].GetName() << " what do you want to bet?" << '\n';
			std::cout << "1) color " << '\n';
			std::cout << "2) number" << '\n';
			std::cout << "3) range " << '\n';
			std::cout << "4) even/not even " << '\n';
			std::cin >> n;

			if (n == 1)
			{
				setplayerbet(i, color);

				int colornum;
				std::cout << "what color do you want to make a bet ?" << '\n';
				std::cout << "1) Red" << '\n';
				std::cout << "2) Black " << '\n';
				std::cin >> colornum;

				if (colornum != 1 && colornum != 2)
				{
					while (colornum != 1 && colornum != 2)
					{
						std::cout << "choose correct number of color";
						std::cin >> colornum;
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
				std::cout << "what number do you want to bet on ?" << '\n';
				std::cin >> number;
				if (number > 36 || number < 0)
				{
					while (number > 36 || number < 0)
					{
						std::cout << "the number you want to bet on should be in the range from 0 to 36, choose another number." << '\n';
						std::cin >> number;
					}
				}

				setplayervalnum(i, number);

				setplayervaliszero(i, (number == 0));

				Players[i].SetBet();
				Players[i].setsummarybet(Players[i].getbet());
				Casinobank += Players[i].getbet();
				Players[i].setcurrbank();
			}

			else if (n == 3)
			{
				setplayerbet(i, range);

				int rangenumber;
				std::cout << "what range do you want to bet on ?" << '\n';
				std::cout << "1) 0 - 17 " << '\n';
				std::cout << "2) 18 - 36 " << '\n';
				std::cin >> rangenumber;

				if (rangenumber != 1 && rangenumber != 2)
				{
					while (rangenumber != 1 && rangenumber != 2)
					{
						std::cout << "enter correct number of range" << '\n';
						std::cin >> rangenumber;
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
				std::cout << "what do you want to bet on ?" << '\n';
				std::cout << "1) not even" << '\n';
				std::cout << "2) is even" << '\n';
				std::cin >> evennum;

				if (evennum != 1 && evennum != 2)
				{
					while (evennum != 1 && evennum != 2)
					{
						std::cout << "choose correct number of your bet" << '\n';
						std::cin >> evennum;
					}
				}
				setplayervaliseven(i, not(evennum == 1));

				Players[i].SetBet();
				Players[i].setsummarybet(Players[i].getbet());
				Casinobank += Players[i].getbet();
				Players[i].setcurrbank();
			}
		}

		RollofRoulete();

		for (int i = 0; i < numofplayers; ++i)
		{

			if (getplayerstavka(i) == color)
			{
				if (getplayervalisblack(i) == getcompblack())
				{
					win(i, Casinobank, 2);
				}
				else
				{
					lose(i, Casinobank);
				}
			}

			else if (getplayerstavka(i) == number)
			{
				if (getplayervalnum(i) == getcompnum())
				{
					win(i, Casinobank, 37);
				}
				else
				{
					lose(i, Casinobank);
				}
			}

			else if (getplayerstavka(i) == even)
			{
				if (getplayervaliseven(i) == getcompeven() && getcompzero() == false)
				{
					win(i, Casinobank, 2);
				}
				else
				{
					lose(i, Casinobank);
				}
			}
			else if (getplayerstavka(i) == range)
			{
				if (getplayervalnum(i) == 17 && getplayervalnum(i) >= getcompnum())
				{
					win(i, Casinobank, 2);
				}
				else if (getplayervalnum(i) == 18 && getplayervalnum(i) <= getcompnum())
				{
					win(i, Casinobank, 2);
				}
				else
				{
					lose(i, Casinobank);
				}
			}
		}

		std::cout << '\n';
		std::cout << "do you want to play again ? " << '\n';
		std::cout << "1) Yes " << '\n';
		std::cout << "0) No " << '\n';
		std::cin >> gamecontinue;
	} while (gamecontinue && isbankrupt() != true && Casinobank > 0);

	for (int i = 0; i < numofplayers; ++i)
	{
		std::cout << Players[i].GetName() << ':' << '\n';
		std::cout << "summary bet = " << Players[i].getsummarybet() << '\n';
		std::cout << "summary prize = " << Players[i].getsummaryprize() << '\n';
	}
}