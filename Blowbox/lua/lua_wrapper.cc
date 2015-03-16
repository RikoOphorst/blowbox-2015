#include "../../blowbox/lua/lua_wrapper.h"

#include "../../blowbox/console/console.h"

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
		Console::Instance()->Log(brief);

		std::string string;

		int top = lua_gettop(L);
		for (int i = 1; i <= top; ++i) {
			int t = lua_type(L, i);

			string = std::to_string(i) + ": ";
			
			string += ConvertElementToString(L, i);

			Console::Instance()->Log(string);
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
	bool LuaWrapper::CompileFromFile(lua_State* L, const std::string& path)
	{
		if (luaL_dofile(L, path.c_str()) != 0)
		{
			Console::Instance()->Log(ConvertElementToString(L, -1), LOG_COLOR_TYPES::LOG_COLOR_ERROR);
			return false;
		}

		return true;
	}

	//------------------------------------------------------------------------------------------------------
	bool LuaWrapper::CompileFromString(lua_State* L, const std::string& code, const std::string& source)
	{
		int stacksize = lua_gettop(L);
		if ((luaL_loadbuffer(L, code.c_str(), strlen(code.c_str()), NULL) || lua_pcall(L, 0, LUA_MULTRET, 0)))
		{
			Console::Instance()->Log(lua_tostring(L, -1), LOG_COLOR_TYPES::LOG_COLOR_ERROR);
			return false;
		}

		if (stacksize != lua_gettop(L))
		{
			for (int i = 1; i <= lua_gettop(L) - stacksize; ++i)
			{
				Console::Instance()->Log(std::string("[OUTPUT] ") + ConvertElementToString(L, i));
			}
		}

		lua_settop(L, stacksize);

		return true;
	}

	//------------------------------------------------------------------------------------------------------
	std::string LuaWrapper::ConvertElementToString(lua_State* L, const int& index)
	{
		int top = lua_gettop(L);
		int t = lua_type(L, index);

		std::string string;

		switch (t)
		{
		case LUA_TSTRING:  // strings
			string = lua_tostring(L, index);
			break;

		case LUA_TBOOLEAN:  // booleans
			string = lua_toboolean(L, index) ? "true" : "false";
			break;

		case LUA_TNUMBER:  // numbers
			string = std::to_string(lua_tonumber(L, index));
			break;

		default:  // other values
			string = lua_typename(L, index);
			break;
		}

		lua_settop(L, top);

		return string;
	}

	//------------------------------------------------------------------------------------------------------
	int LuaWrapper::StackTrace(lua_State* L)
	{
		lua_getfield(L, LUA_GLOBALSINDEX, "debug");
		lua_getfield(L, -1, "traceback");
		lua_pushvalue(L, 1);
		lua_pushinteger(L, 2);
		lua_call(L, 2, 1);

		Console::Instance()->Log(lua_tostring(L, -1), LOG_COLOR_TYPES::LOG_COLOR_NOTICE);

		lua_pop(L, 2);

		return 0;
	}

	//------------------------------------------------------------------------------------------------------
	int LuaWrapper::LuaStackTrace(lua_State* L)
	{	
		lua_getfield(L, LUA_GLOBALSINDEX, "debug");
		lua_getfield(L, -1, "traceback");
		lua_pushvalue(L, 1);
		lua_pushinteger(L, 2);
		lua_call(L, 2, 1);

		Console::Instance()->Log(lua_tostring(L, -1), LOG_COLOR_TYPES::LOG_COLOR_NOTICE);

		lua_pop(L, 2);

		return 0;
	}
}