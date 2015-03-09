#include "../blowbox/game.h"
#include "../blowbox/elements/quad.h"
#include "../blowbox/utility/lua_enum.h"

#include "../blowbox/lua/lua_register.h"

using namespace blowbox;

int main(int argc, char** argv)
{
	AllocatedMemory& memory = AllocatedMemory::Instance();
	
	LuaRegister::Instance()->RegisterSingleton<Game>(LuaState::Instance()->Get());
	LuaRegister::Instance()->RegisterClass<Quad>(LuaState::Instance()->Get());
	LuaRegister::Instance()->RegisterClass<LuaEnum>(LuaState::Instance()->Get());

	Game::Instance()->Run();

	return EXIT_SUCCESS;
}