#pragma once

#include "../../blowbox/lua/lua_class.h"
#include <vector>
#include <map>

namespace blowbox
{
	class LuaEnum : public LuaClass
	{
	public:
		LuaEnum(lua_State* L);

		~LuaEnum();

		static int LuaReset(lua_State* L);

		static void LuaRegisterFunctions(lua_State* L);

		CLASSNAME("enum");
	};
}