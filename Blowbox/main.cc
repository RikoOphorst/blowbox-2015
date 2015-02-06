#include "game.h"

#include "console\console.h"

using namespace blowbox;

int main (int argc, char** argv)
{
	QApplication QApp(argc, argv);

	for (int i = 0; i < argc; ++i)
	{
		if (strcmp(argv[i], "-console") == 0) { Console::Instance()->Show(); }
		if (strcmp(argv[i], "-src") == 0) { std::cout << argv[i + 1] << std::endl; }
	}

	allocated_memory();
	SharedPtr<Game> game(new Game());

	game->CreateWin32("Blowbox", 640, 480);
	game->CreateDisplayDevice();

	game->Run();

	return EXIT_SUCCESS;
}