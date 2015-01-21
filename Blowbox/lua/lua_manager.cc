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
		state_ = lua_open();
		luaopen_base(state_);
		luaopen_io(state_);
		luaopen_string(state_);
		luaopen_math(state_);
	};

	LuaManager::~LuaManager() 
	{

	};

	LuaManager* LuaManager::Instance()
	{
		static SharedPtr<LuaManager> ptr(new LuaManager());
		return ptr.get();
	}

	void LuaManager::MakeError(std::string err)
	{
		std::cout << "Lua error: " << err << std::endl;
	}

	void LuaManager::LoadScript(std::string path, bool reloading)
	{
		if (luaL_dofile(state_, path.c_str()))
			MakeError(lua_tostring(state_, -1));

		lua_getglobal(state_, "tree");
		std::cout << "tree is " << lua_tonumber(state_, -1) << std::endl;

		if (!reloading)
		{
			FileWatch::Instance()->Add(path, FileType::Script);
		}
	}
}