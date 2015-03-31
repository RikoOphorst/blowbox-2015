#include "../../blowbox/lua/lua_wrapper.h"

#include "../../blowbox/console/console.h"

#include "../../blowbox/win32/file_watch.h"

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
			
			string += ToString(L, i);

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
	bool LuaWrapper::CompileFromFile(lua_State* L, const std::string& path, bool reloading)
	{
		if (luaL_dofile(L, path.c_str()) != 0)
		{
			Console::Instance()->Log(ToString(L, -1), LOG_COLOR_TYPES::LOG_COLOR_ERROR);
			return false;
		}

		if (!reloading)
		{
			FileWatch::Instance()->Add(path, WATCH_FILE_TYPES::WATCH_FILE_SCRIPT);
		}

		Console::Instance()->Log("[LUA] Compiled file: " + path, LOG_COLOR_TYPES::LOG_COLOR_NOTICE);

		return true;
	}

	//------------------------------------------------------------------------------------------------------
	bool LuaWrapper::CompileFromString(lua_State* L, const std::string& code, const std::string& source)
	{
		int stacksize = lua_gettop(L);
		if (luaL_dostring(L, code.c_str()))
		{
			Console::Instance()->Log(lua_tostring(L, -1), LOG_COLOR_TYPES::LOG_COLOR_ERROR);
			return false;
		}

		if (stacksize != lua_gettop(L))
		{
			for (int i = 1; i <= lua_gettop(L) - stacksize; ++i)
			{
				Console::Instance()->Log(std::string("[OUTPUT] ") + ToString(L, i));
			}
		}

		lua_settop(L, stacksize);

		return true;
	}

	//------------------------------------------------------------------------------------------------------
	int LuaWrapper::ToRelative(lua_State* L, const int& absolute)
	{
		if (absolute <= 0)
			return absolute;

		return -(lua_gettop(L) - absolute + 1);
	}

	//------------------------------------------------------------------------------------------------------
	int LuaWrapper::ToAbsolute(lua_State* L, const int& relative)
	{
		if (relative >= 0)
			return relative;

		return lua_gettop(L) + 1 + relative;
	}

	//------------------------------------------------------------------------------------------------------
	int LuaWrapper::ToArgument(lua_State* L, const int& index)
	{
		if (index < 0)
		{
			// relative index
			return ToAbsolute(L, index);
		}
		else if (index > 0)
		{
			// absolute index
			return index;
		}
		
		return 0;
	}

	//------------------------------------------------------------------------------------------------------
	std::string LuaWrapper::ToString(lua_State* L, const int& index)
	{
		int top = lua_gettop(L);

		std::string string;

		switch (Typename(L, index))
		{
		case LUA_TYPE::LUA_TYPE_STRING:  // strings
			string = lua_tostring(L, index);
			break;

		case LUA_TYPE::LUA_TYPE_USERDATA: // userdata
		case LUA_TYPE::LUA_TYPE_LIGHTUSERDATA:

			lua_pushvalue(L, index);
			lua_getglobal(L, "tostring");
			lua_pushvalue(L, -2);
			lua_pcall(L, 1, 1, 0);

			string = lua_tostring(L, -1);
			break;

		case LUA_TYPE::LUA_TYPE_BOOLEAN:
			string = lua_toboolean(L, index) ? "true" : "false";
			break;

		case LUA_TYPE::LUA_TYPE_NUMBER:
			string = std::to_string(lua_tonumber(L, index));
			break;

		case LUA_TYPE::LUA_TYPE_FUNCTION:
			string = "function";
			break;

		case LUA_TYPE::LUA_TYPE_NIL:
		case LUA_TYPE::LUA_TYPE_NONE:
			string = "nil";
			break;

		case LUA_TYPE::LUA_TYPE_TABLE:
			string = "table";
			break;

		default:
			string = lua_typename(L, index);
			break;
		}

		lua_settop(L, top);

		return string;
	}

	//------------------------------------------------------------------------------------------------------
	std::map<std::string, LuaValue> LuaWrapper::ToTable(lua_State* L, const int& index)
	{
		int idx = ToAbsolute(L, index);

		std::map<std::string, LuaValue> table;

		if (lua_istable(L, idx))
		{
			lua_pushnil(L);

			while (lua_next(L, idx))
			{
				std::map<std::string, LuaValue> element;
				LuaValue value;
				std::string identifier;
				
				switch (lua_type(L, -1))
				{
				case LUA_TTABLE:
					element = ToTable(L, -1);

					value.type = LUA_TYPE::LUA_TYPE_TABLE;
					value.location = LUA_LOCATION::LUA_LOCATION_FIELD;
					
					if (Typename(L, -2) == LUA_TYPE::LUA_TYPE_NUMBER)
					{
						value.identifier = ToString(L, -2);
						value.identifier = value.identifier.substr(0, value.identifier.find('.'));
					}
					else
					{
						value.identifier = ToString(L, -2);
					}

					value.value = ToString(L, -1);

					table.emplace(value.identifier, value);

					identifier = value.identifier;

					for (auto it = element.begin(); it != element.end(); ++it)
					{
						value.type = it->second.type;
						value.location = it->second.location;
						value.identifier = it->second.identifier;
						value.value = it->second.value;

						table.find(identifier)->second.fields.emplace(value.identifier, value);
					}

					lua_pop(L, 1);
					break;
				default:
					value.type = Typename(L, -1);
					value.location = LUA_LOCATION::LUA_LOCATION_FIELD;

					if (Typename(L, -2) == LUA_TYPE::LUA_TYPE_NUMBER)
					{
						value.identifier = ToString(L, -2);
						value.identifier = value.identifier.substr(0, value.identifier.find('.'));
					}
					else
					{
						value.identifier = ToString(L, -2);
					}
					value.value = ToString(L, -1);

					table.emplace(value.identifier, value);

					lua_pop(L, 1);
					break;
				}
			}
		}
		else
		{
			luaL_typerror(L, index, "table");
		}

		return table;
	}

	//------------------------------------------------------------------------------------------------------
	LUA_TYPE LuaWrapper::Typename(lua_State* L, const int& index)
	{
		LUA_TYPE type;
		
		switch (lua_type(L, index))
		{
		case LUA_TSTRING:
			type = LUA_TYPE::LUA_TYPE_STRING;
			break;

		case LUA_TUSERDATA:
			type = LUA_TYPE::LUA_TYPE_USERDATA;

			break; 
		case LUA_TLIGHTUSERDATA:
			type = LUA_TYPE::LUA_TYPE_LIGHTUSERDATA;
			break;

		case LUA_TBOOLEAN:
			type = LUA_TYPE::LUA_TYPE_BOOLEAN;
			break;

		case LUA_TNUMBER:
			type = LUA_TYPE::LUA_TYPE_NUMBER;
			break;

		case LUA_TFUNCTION:
			type = LUA_TYPE::LUA_TYPE_FUNCTION;
			break;

		case LUA_TNIL:
			type = LUA_TYPE::LUA_TYPE_NIL;
			break;

		case LUA_TNONE:
			type = LUA_TYPE::LUA_TYPE_NONE;
			break;

		case LUA_TTABLE:
			type = LUA_TYPE::LUA_TYPE_TABLE;
			break;

		default:
			type = LUA_TYPE::LUA_TYPE_UNKNOWN;
			break;
		}

		return type;
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