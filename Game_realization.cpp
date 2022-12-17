#include "casino.h"
bool Game::isequal()
{
	for (int i = 0; i < numofplayers - 1; ++i)
	{
		if (Players[i].getbet() != Players[i + 1].getbet())
		{
			return false;
		}
	}
	return true;
}
bool Game::isbankrupt()
{
	for (int i = 0; i < numofplayers; ++i)
	{
		if (Players[i].getbank() == 0)
		{
			return true;
		}
	}
	return false;
}

Game::Game(std::unique_ptr<Player[]> Playerss, Host Croupier, int numofplayers) :Croupier(Croupier), numofplayers(numofplayers){
	Players = std::move(Playerss);
};
Game::Game(){};