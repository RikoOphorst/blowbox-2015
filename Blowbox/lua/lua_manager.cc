#include "lua_manager.h"



void error(const char *fmt, ...) {
	va_list argp;
	va_start(argp, fmt);
	vfprintf(stderr, fmt, argp);
	va_end(argp);
}

namespace blowbox
{
	LuaManager::LuaManager() 
	{
		_state = lua_open();
		luaopen_base(_state);
		luaopen_io(_state);
		luaopen_string(_state);
		luaopen_math(_state);
	};

	LuaManager::~LuaManager() 
	{

	};

	LuaManager* LuaManager::Instance()
	{
		static SharedPtr<LuaManager> ptr(new LuaManager());
		return ptr.get();
	}

	void LuaManager::LoadScript(std::string path)
	{
		if (luaL_loadfile(_state, path.c_str()) || lua_pcall(_state, 0, 0, 0))
			error("cannot run file: %s", lua_tostring(_state, -1));

		lua_getglobal(_state, "tree");
		std::cout << "tree is " << (int)lua_tonumber(_state, -1) << std::endl;
	}
}