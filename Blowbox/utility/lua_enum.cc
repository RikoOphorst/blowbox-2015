#include "../../blowbox/utility/lua_enum.h"

namespace blowbox
{
	LuaEnum::LuaEnum(lua_State* L)
	{
		LuaReset(L);
	}

	LuaEnum::~LuaEnum()
	{

	}

	void LuaEnum::RegisterFunctions(lua_State* L)
	{
		luaL_Reg regist[] = {
			{ "reset", LuaReset }
			{ NULL, NULL }
		};

		luaL_register(L, NULL, regist);
	}

	int LuaEnum::LuaReset(lua_State* L)
	{
		LuaEnum* self = LuaWrapper::Instance()->ParseUserdata<LuaEnum>(L, 1);

		// Create the enumerator table
		lua_newtable(L);
		int enumerator = lua_gettop(L);

		// Push a nil value for the first iteration
		lua_pushnil(L);
		
		while (lua_next(L, -3) != 0)
		{
			lua_pushvalue(L);
		}
	}
}