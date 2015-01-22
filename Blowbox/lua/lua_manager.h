#pragma once

extern "C"
{
	#include <lua.h>
	#include <lauxlib.h>
	#include <lualib.h>
}

#include "../memory/shared_ptr.h"
#include "../win32/file_watch.h"

namespace blowbox
{
	class LuaManager
	{
	public:
		LuaManager();
		~LuaManager();

		static LuaManager* Instance();

		void LoadScript(std::string path, bool reloading = false);

		void MakeError(std::string);

		lua_State* GetState();
	private:
		lua_State* state_;
	};
}