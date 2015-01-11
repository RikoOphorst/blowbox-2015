#pragma once

extern "C"
{
	#include <lua.h>
	#include <lauxlib.h>
	#include <lualib.h>
}

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "../memory/shared_ptr.h"

namespace blowbox
{
	class LuaManager
	{
	public:
		LuaManager();
		~LuaManager();

		static LuaManager* Instance();

		void LoadScript(std::string path);

	private:
		lua_State* _state;
	};
}