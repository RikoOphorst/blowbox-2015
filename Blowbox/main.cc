#include "game.h"

#include "../blowbox/lua/lua_register.h"

using namespace blowbox;

int main(int argc, char** argv)
{
	AllocatedMemory& memory = AllocatedMemory::Instance();
	
	LuaState::Instance();

	Game::Instance()->Run();

	return EXIT_SUCCESS;
}