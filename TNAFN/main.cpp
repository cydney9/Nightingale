#include "Game.h"

#undef main
int main()
{
	int frameTime;

	//Create the Game
	Game game;

	//Initialize the game
	game.InitGame();

	//Runs the game until it returns :)
	return game.Run();
}