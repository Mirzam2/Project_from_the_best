#include "casino.h"
bool Game::isequal() {
	std::cout << "isequal ";
	std::cout << numofplayers << " ";
	for (int i = 0; i < numofplayers-1; i++) {
		std::cout << i << " is ok ";
		if (Players[i].getbet() != Players[i + 1].getbet()) {
			std::cout << " false \n";
			return false;}
	}
	cout << " true \n";
	return true;
}
bool Game::isbankrupt() {
	std::cout << "isbankrupt \n";
	std::cout << numofplayers << " ";
	for (int i = 0; i < numofplayers; i++) {
		if (Players[i].getbank() == 0) {return true;}
	}
	return false;
}

Game::Game(Player *Players, Host Croupier, int numofplayers) : Players(Players), Croupier(Croupier), numofplayers(numofplayers){};
Game::Game(){};