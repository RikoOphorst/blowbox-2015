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

	//------------------------------------------------------------------------------------------------------
	void LuaWrapper::CreateWeakTable(lua_State* L)
	{
		// Make sure the stack is big enough for this operation to be possible
		lua_checkstack(L, 3);

		// Create the actual weak table
		lua_newtable(L);

		// Copy the weak table which will be used as the metatable
		lua_pushvalue(L, -1);

		// Set the meta table to the actual weak table
		lua_setmetatable(L, -2);

		// Push the literal __mode
		lua_pushliteral(L, "__mode");

		// Push the actual mode value
		lua_pushstring(L, "v");

		// Set the value: -3[__mode] = "v"
		lua_settable(L, -3);
	}

	//------------------------------------------------------------------------------------------------------
	void LuaWrapper::CompileFromFile(lua_State* L, const std::string& path)
	{
		if (luaL_loadfile(L, path.c_str()))
		{
			BLOW_BREAK(lua_tostring(L, lua_gettop(L)));
		}
		else
		{
			if (lua_pcall(L, 0, LUA_MULTRET, 0))
			{
				BLOW_BREAK(lua_tostring(L, lua_gettop(L)));
			}
		}
	}

	//------------------------------------------------------------------------------------------------------
	void LuaWrapper::CompileFromString(lua_State* L, const std::string& code, const std::string& source)
	{
		if ((luaL_loadbuffer(L, code.c_str(), strlen(code.c_str()), source.c_str()) || lua_pcall(L, 0, 0, 0)))
		{
			BLOW_BREAK(lua_tostring(L, lua_gettop(L)));
		}
	}
}