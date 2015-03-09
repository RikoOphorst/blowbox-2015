#include "../../blowbox/utility/lua_enum.h"

#include "../../blowbox/lua/lua_wrapper.h"

namespace blowbox
{
	LuaEnum::LuaEnum(lua_State* L)
	{
		LuaReset(L);
	}

	LuaEnum::~LuaEnum()
	{

	}

	void LuaEnum::LuaRegisterFunctions(lua_State* L)
	{
		luaL_Reg regist[] = {
			{ "reset", LuaReset },
			{ NULL, NULL }
		};

		luaL_register(L, NULL, regist);
	}

	int LuaEnum::LuaReset(lua_State* L)
	{
		const char* identifier = LuaWrapper::Instance()->Get<const char*>(L, -2);

		// Create the enumerator table
		lua_newtable(L);

		// Keep the index of where the table is on the stack
		int enumerator = lua_gettop(L);

		// Push a nil value for the first iteration
		lua_pushnil(L);
		
		unsigned int i = 0;

		while (lua_next(L, -3) != 0)
		{
			// Copy the name
			lua_pushvalue(L, -1);

			// Push the integer
			lua_pushnumber(L, static_cast<lua_Number>(i++));

			// Set the key value pair
			lua_settable(L, enumerator);

			// Pop the value on the top of the stack
			lua_pop(L, 1);
		}

		// Set it on the global buffer
		lua_setglobal(L, identifier);

		return 0;
	}
}