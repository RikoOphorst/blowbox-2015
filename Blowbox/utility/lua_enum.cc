#include "../../blowbox/utility/lua_enum.h"

#include "../../blowbox/lua/lua_wrapper.h"

namespace blowbox
{
	//------------------------------------------------------------------------------------------------------
	LuaEnum::LuaEnum()
	{
		
	}
	
	//------------------------------------------------------------------------------------------------------
	LuaEnum::LuaEnum(lua_State* L)
	{
		LuaReset(L);
	}

	//------------------------------------------------------------------------------------------------------
	LuaEnum::~LuaEnum()
	{

	}

	//------------------------------------------------------------------------------------------------------
	void LuaEnum::Set(lua_State* L, const std::string& identifier, const std::vector<std::string>& types)
	{
		// Save the stack size before doing any crazy things with it
		int stacksize = lua_gettop(L);

		// Create the enumerator table and save its stack index
		lua_newtable(L);
		int enumerator = lua_gettop(L);

		for (unsigned int i = 0; i < types.size(); ++i)
		{
			// Push type string on the stack
			lua_pushstring(L, types.at(i).c_str());

			// Push the number on the stack
			lua_pushnumber(L, i);

			// Set the key value pair onto the enumerator
			lua_settable(L, enumerator);
		}

		// Set the enumerator on the global table
		lua_setglobal(L, identifier.c_str());

		// Clear the stack
		lua_settop(L, stacksize);
	}

	//------------------------------------------------------------------------------------------------------
	void LuaEnum::LuaRegisterFunctions(lua_State* L)
	{
		luaL_Reg regist[] = {
			{ "reset", LuaReset },
			{ NULL, NULL }
		};

		luaL_register(L, NULL, regist);
	}

	//------------------------------------------------------------------------------------------------------
	int LuaEnum::LuaReset(lua_State* L)
	{
		const char* identifier = LuaWrapper::Instance()->Get<const char*>(L, 1);

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