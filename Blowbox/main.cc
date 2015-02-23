#include "game.h"

using namespace blowbox;

int main(int argc, char** argv)
{
	Game::Instance()->Run();

	return EXIT_SUCCESS;
}