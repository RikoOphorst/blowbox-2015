#include "../blowbox/game.h"
#include "../blowbox/elements/quad.h"
#include "../blowbox/utility/lua_enum.h"

#include "../blowbox/lua/lua_register.h"

#include "../blowbox/console/console.h"

using namespace blowbox;

int main(int argc, char** argv)
{
	AllocatedMemory& memory = AllocatedMemory::Instance();

	LuaRegister::Instance()->RegisterSingleton<Game>(LuaState::Instance()->Get());
	LuaRegister::Instance()->RegisterSingleton<Console>(LuaState::Instance()->Get());
	LuaRegister::Instance()->RegisterClass<Quad>(LuaState::Instance()->Get());
	LuaRegister::Instance()->RegisterClass<LuaEnum>(LuaState::Instance()->Get());

	QApplication QApp(argc, argv);
	Console::Instance();

	Game::Instance()->Run();

	return QApp.exec();
}