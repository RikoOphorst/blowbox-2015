#include "game.h"

using namespace blowbox;

int main(int argc, char** argv)
{
	AllocatedMemory& memory = AllocatedMemory::Instance();
	Game::Instance()->Run();

	return EXIT_SUCCESS;
}