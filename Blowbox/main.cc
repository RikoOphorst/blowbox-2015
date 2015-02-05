#include "game.h"

using namespace blowbox;

int main (int argc, char** argv)
{



	allocated_memory();
	SharedPtr<Game> game(new Game());

	game->CreateWin32("Blowbox", 640, 480);
	game->CreateDisplayDevice();

	game->Run();

	return EXIT_SUCCESS;
}