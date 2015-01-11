#include "game.h"
#include "lua/lua_manager.h"

using namespace blowbox;

int main (int argc, char** argv)
{
	SharedPtr<Game> game(new Game());

	LuaManager* luaManager = LuaManager::Instance();

	luaManager->LoadScript("C:\\Users\\Riko pc\\script\\myfile.lua");

	/*char buff[256];
	int error;

	lua_State *L = lua_open();
	luaopen_base(L);             /* opens the basic library 
	luaopen_table(L);            /* opens the table library 
	luaopen_io(L);               /* opens the I/O library 
	luaopen_string(L);           /* opens the string lib. 
	luaopen_math(L);             /* opens the math lib. 

	lua_pushboolean(L, true);

	while (fgets(buff, sizeof(buff), stdin) != NULL) {
		error = luaL_loadbuffer(L, buff, strlen(buff), "line") ||
			lua_pcall(L, 0, 0, 0);
		if (error) {
			fprintf(stderr, "%s", lua_tostring(L, -1));
			lua_pop(L, 1);  /* pop error message from the stack 
		}
	} 

	lua_close(L);*/

	game->CreateWin32("Blowbox", 640, 480);
	game->CreateDisplayDevice();

	game->Run();

	return EXIT_SUCCESS;
}