//----------------------------------------------------------------------------
// This is the entry-point for your game.
// Creates and runs the Game2D class which contains the game loop.
//----------------------------------------------------------------------------
#include <crtdbg.h>
#include <random>
#include <time.h>
#include "Game2D.h"

int main() 
{
	// Check for memeory leaks.
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// Creating seed for random.
	srand((unsigned int)time(0));

	// Create the Application.
	Game2D* game = new Game2D("Zombie Survival", 1280, 720, false);

	// Run the game loop.
	game->Run();

	// Clean up.
	delete game;

	return 0;
}