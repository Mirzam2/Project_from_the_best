#include "casino.h";
using namespace std;

void Roulete::initplayervalues(int n) {
	playervalues = new rouletevalue[n];
}

void Roulete::setplayervalnum(int index, int a) {
	playervalues[index].value = a;
}

void Roulete::setplayervalisblack(int index, bool color) {
	playervalues[index].isblack = color;
}

void Roulete::setplayervaliseven(int index, bool even) {
	playervalues[index].isblack = even;
}

void Roulete::setplayervaliszero(int index, bool zero) {
	playervalues[index].iszero = zero;
}

void Roulete::setplayerbet(int index, stavka stavka) {
	playervalues[index].playerbet = stavka;
}

int Roulete::getplayervalnum(int index) {
	return playervalues[index].value;
}

bool Roulete::getplayervalisblack(int index) {
	return playervalues[index].isblack;
}

bool Roulete::getplayervaliseven(int index) {
	return playervalues[index].iseven;
}

bool Roulete::getplayervaliszero(int index) {
	return playervalues[index].iszero;
}

stavka Roulete::getplayerstavka(int index) {
	return playervalues[index].playerbet;
}

void Roulete::RollofRoulete() {
	srand(time(0));

	int* blacknums = new int[18]{ 2, 4, 6, 8, 10, 11, 13, 15, 17, 20, 22, 24, 26, 28, 29, 31, 33, 35 };

	computerval.value = rand() % 37;

	if (computerval.value == 0) { computerval.iszero = 1; }
	else {
		computerval.iszero = 0;
		if (computerval.value % 2 == 0) { computerval.iseven = 1; }
		else computerval.iseven = 0;
	}

	int* numblack = new int;
	*numblack = 0;

	for (int i = 0; i < 18; i++) {
		if (computerval.value == blacknums[i]) {
			(*numblack)++;
			break;
		}
	}

	if (*numblack != 0) { computerval.isblack = true; }
	else computerval.isblack = false;

	delete numblack;
	delete[] blacknums;
}

int Roulete::getcompnum() {
	return computerval.value;
}

bool Roulete::getcompblack() {
	return computerval.isblack;
}

bool Roulete::getcompeven() {
	return computerval.iseven;
}

bool Roulete::getcompzero() {
	return computerval.iszero;
}
