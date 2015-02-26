#include "game.h"

using namespace blowbox;

int main(int argc, char** argv)
{
	Game* game = Game::Instance();
	game->Run();

	return EXIT_SUCCESS;
}