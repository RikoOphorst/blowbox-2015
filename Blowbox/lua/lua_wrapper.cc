#include "../../blowbox/lua/lua_wrapper.h"

namespace blowbox
{
	//------------------------------------------------------------------------------------------------------
	LuaWrapper::LuaWrapper()
	{

	}

	//------------------------------------------------------------------------------------------------------
	LuaWrapper::~LuaWrapper()
	{

	}

	//------------------------------------------------------------------------------------------------------
	LuaWrapper* LuaWrapper::Instance()
	{
		static SharedPtr<LuaWrapper> ptr(new LuaWrapper());
		return ptr.get();
	}

	//------------------------------------------------------------------------------------------------------
	void LuaWrapper::Dump(lua_State* L, const std::string& brief)
	{
		printf("%s\n", brief.c_str());
		int i;
		int top = lua_gettop(L);
		for (i = 1; i <= top; i++) {
			int t = lua_type(L, i);
			
			printf("%i:", i);
			
			switch (t) {

			case LUA_TSTRING:  // strings
				printf("'%s'", lua_tostring(L, i));
				break;

			case LUA_TBOOLEAN:  // booleans
				printf(lua_toboolean(L, i) ? "true" : "false");
				break;

			case LUA_TNUMBER:  // numbers
				printf("%g", lua_tonumber(L, i));
				break;

			default:  // other values
				printf("%s", lua_typename(L, t));
				break;

			}

			printf("\n");
		}
	}
}