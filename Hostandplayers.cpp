#include "casino.h"

void Host::SetName(){
	srand(time(0));

	int f = rand() % croupiernames->size();

	name = croupiernames[f];
}

void Player::SetName() {
	cin >> name;
}

void Host::BidsCollect(int a) {
	Bets = a;
}

int Host::Giveprize() {
	return Bets;
	Bets = 0;
}

void Player::setwin(bool a) {
	Iswinner = a;
}

bool Player::getwin() {
	return Iswinner;
}

void Player::setsummarybet(int a) {
	summarybet += a;
}

void Player::SetPrize(int a) {
	summaryprize += a;
	prizesumm = a;
}

int Player::getcurrprize() {
	return prizesumm;
}

int Player::getsummarybet() {
	return summarybet;
	summarybet = 0;
}

int Player::getsummaryprize() {
	return summaryprize;
	summaryprize = 0;
}
int Player::getbank() {
	return bank;
}

int Player::getprize() {
	return prizesumm;
}

int Player::getbet() {
	return bet;
}

void Player::SetintBank() {
	cout << "How much coins you have for this Player ?" << endl;
	cin >> bank;
	if (bank <= 0) {
		while (bank <= 0) {
			cout << "you can't play without coins, enter bank" << endl;
			cin >> bank;
		}
	}
}

void Player::SetBet() {
	cout << "How much coins do you want to bet ?" << endl;
	cin >> bet;
	if (bet > bank || bet == 0) {
		while (bet > bank || bet == 0) {
			cout << "you can't bet that much, change the bid" << endl;
			cin >> bet;
		}
	}
	cout << "You made a bet of " << bet << " coins" << endl;
}

void Player::setcurrbank() {
	bank -= bet;
	cout << "In your bank now " << bank << " coins" << endl;
}

void Player::SetoutBank() {
	bank += prizesumm;
	cout << "After Player your bank is " << bank << " coins" << endl;
}