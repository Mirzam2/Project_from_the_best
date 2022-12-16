#include "casino.h"
using namespace std;

string coutblack(bool isblack) {
	string black;
	if (isblack == true) { black = "black"; }
	else black = "red";
	return black;
}

string couteven(bool iseven) {
	string chet;
	if (iseven == true) { chet = "even"; }
	else chet = "not even";
	return chet;
}

void Casino::Setnumofplayers() { 
	cin >> numofplayers;
	Players = new Player[numofplayers];
}

int Casino::Getnumofplayers() {
	return numofplayers;
}

void Casino::Initplayers() {
	for (int i = 0; i < numofplayers; i++) {
		cout << "Enter name of " << i + 1 << " player" << endl;
		Players[i].SetName();
	}
}

void Casino::game() {

	int gamenumber;
	cout << "Enter num of players" << endl;
	Setnumofplayers();
	Initplayers();

	cout << "there are list of our games, which you want to play ?" << endl;//Выбор игры, можно в отдельное место
	cout << "1) dices" << endl;
	cout << "2) roulete" << endl;
	cin >> gamenumber;

	if (gamenumber != 1 && gamenumber != 2) { //проверка на то что выбрал правильно
		cout << "choose correct number of game" << endl;
		cin >> gamenumber;
	}
	Croupier.SetName();
		cout << "your croupier is " << Croupier.GetName() << endl;
	if (gamenumber == 1) {

		
		Dices play(Players,Croupier, numofplayers);
		play.game_process();
	}

	else {
		int* gamecontinue = new int;

		Roulete play;

		for (int i = 0; i < numofplayers; i++) {
			cout << Players[i].GetName() << ' ';
			Players[i].SetintBank();
		}

		play.initplayervalues(numofplayers);

		do {
			for (int i = 0; i < numofplayers; i++) {
				int n;
				cout << Players[i].GetName() << " what do you want to bet ?" << endl;
				cout << "1) color " << endl;
				cout << "2) number" << endl;
				cout << "3) range " << endl;
				cout << "4) even/not even " << endl;
				cin >> n;
				
				if (n == 1) {
					play.setplayerbet(i, color);

					int colornum;
					cout << "what color do you want to make a bet ?" << endl;
					cout << "1) Red" << endl;
					cout << "2) Black " << endl;
					cin >> colornum;

					if (colornum != 1 && colornum != 2) {
						while (colornum != 1 && colornum != 2) {
							cout << "choose correct number of color";
							cin >> colornum;
						}
					}

					if (colornum == 1) { play.setplayervalisblack(i, false); }
					else play.setplayervalisblack(i, true);

					Players[i].SetBet();
					Players[i].setsummarybet(Players[i].getbet());
					Casinobank += Players[i].getbet();
					Players[i].setcurrbank();

				}

				else if (n == 2) {
					play.setplayerbet(i, number);

					int number;
					cout << "what number do you want to bet on ?" << endl;
					cin >> number;
					if (number > 36 || number < 0) {
						while (number > 36 || number < 0) {
							cout << "the number you want to bet on should be in the range from 0 to 36, choose another number." << endl;
							cin >> number;
						}
					}

					play.setplayervalnum(i, number);
					if (number == 0) { play.setplayervaliszero(i, true); }
					else play.setplayervaliszero(i, false);

					Players[i].SetBet();
					Players[i].setsummarybet(Players[i].getbet());
					Casinobank += Players[i].getbet();
					Players[i].setcurrbank();
				}

				else if (n == 3) {
					play.setplayerbet(i, range);

					int rangenumber;
					cout << "what range do you want to bet on ?" << endl;
					cout << "1) 0 - 17 " << endl;
					cout << "2) 18 - 36 " << endl;
					cin >> rangenumber;

					if (rangenumber != 1 && rangenumber != 2) {
						while (rangenumber != 1 && rangenumber != 2) {
							cout << "enter correct number of range" << endl;
							cin >> rangenumber;
						}
					}

					if (rangenumber == 1) { play.setplayervalnum(i, 17); }
					else play.setplayervalnum(i, 18);

					Players[i].SetBet();
					Players[i].setsummarybet(Players[i].getbet());
					Casinobank += Players[i].getbet();
					Players[i].setcurrbank();
				}

				else {
					play.setplayerbet(i, even);

					int evennum;
					cout << "what do you want to bet on ?" << endl;
					cout << "1) not even" << endl;
					cout << "2) is even" << endl;
					cin >> evennum;

					if (evennum != 1 && evennum != 2) {
						while (evennum != 1 && evennum != 2) {
							cout << "choose correct number of your bet" << endl;
							cin >> evennum;
						}
					}

					if (evennum == 1) { play.setplayervaliseven(i, false); }
					else play.setplayervaliseven(i, true);

					Players[i].SetBet();
					Players[i].setsummarybet(Players[i].getbet());
					Casinobank += Players[i].getbet();
					Players[i].setcurrbank();
				}
			}

			play.RollofRoulete();

			for (int i = 0; i < numofplayers; i++) {

				if (play.getplayerstavka(i) == color) {
					if (play.getplayervalisblack(i) == play.getcompblack()) {
						Players[i].SetPrize(2 * Players[i].getbet());
						Casinobank -= Players[i].getcurrprize();
						cout << Players[i].GetName() << " ,you win, your prizesumm " << Players[i].getcurrprize() << endl;
						Players[i].SetoutBank();
					}
					else {
						Players[i].SetPrize(0);
						Casinobank -= Players[i].getcurrprize();
						cout << Players[i].GetName() << " you loose" << endl;
						Players[i].SetoutBank();
					}
				}

				else if (play.getplayerstavka(i) == number) {
					if (play.getplayervalnum(i) == play.getcompnum()) {
						Players[i].SetPrize(37 * Players[i].getbet());
						Casinobank -= Players[i].getcurrprize();
						cout << Players[i].GetName() << " ,you win, your prizesumm " << Players[i].getcurrprize() << endl;
						Players[i].SetoutBank();
					}
					else {
						Players[i].SetPrize(0);
						Casinobank -= Players[i].getcurrprize();
						cout << Players[i].GetName() << " you loose" << endl;
						Players[i].SetoutBank();
					}
				}

				else if (play.getplayerstavka(i) == even) {
					if (play.getplayervaliseven(i) == play.getcompeven() && play.getcompzero() == false) {
						Players[i].SetPrize(2 * Players[i].getbet());
						Casinobank -= Players[i].getcurrprize();
						cout << Players[i].GetName() << " ,you win, your prizesumm " << Players[i].getcurrprize() << endl;
						Players[i].SetoutBank();
					}
					else {
						Players[i].SetPrize(0);
						Casinobank -= Players[i].getcurrprize();
						cout << Players[i].GetName() << " you loose" << endl;
						Players[i].SetoutBank();
					}
				}
				else if (play.getplayerstavka(i) == range) {
					if (play.getplayervalnum(i) == 17 && play.getplayervalnum(i) >= play.getcompnum()) {
						Players[i].SetPrize(2 * Players[i].getbet());
						Casinobank -= Players[i].getcurrprize();
						cout << Players[i].GetName() << " ,you win, your prizesumm " << Players[i].getcurrprize() << endl;
						Players[i].SetoutBank();
					}
					else if (play.getplayervalnum(i) == 18 && play.getplayervalnum(i) <= play.getcompnum()) {
						Players[i].SetPrize(2 * Players[i].getbet());
						Casinobank -= Players[i].getcurrprize();
						cout << Players[i].GetName() << " ,you win, your prizesumm " << Players[i].getcurrprize() << endl;
						Players[i].SetoutBank();
					}
					else {
						Players[i].SetPrize(0);
						Casinobank -= Players[i].getcurrprize();
						cout << Players[i].GetName() << " you loose" << endl;
						Players[i].SetoutBank();
					}
				}
			}

			play.isbankrupt();

			cout << endl;
			cout << "do you want to play again ? " << endl;
			cout << "1) yes " << endl;
			cout << "2) no " << endl;

			cin >> *gamecontinue;
		} while (*gamecontinue != 2 && play.isbankrupt() != true && Casinobank > 0);

		for (int i = 0; i < numofplayers; i++) {
			cout << Players[i].GetName() << ':' << endl;
			cout << "summary bet = " << Players[i].getsummarybet() << endl;
			cout << "summary prize = " << Players[i].getsummaryprize() << endl;
		}
		delete gamecontinue;

	}
}
