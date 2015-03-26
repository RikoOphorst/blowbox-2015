#include "../../blowbox/lua/lua_class.h"

namespace blowbox
{
	std::map<std::string, lua_CFunction> LuaClass::lua_functions;

	//------------------------------------------------------------------------------------------------------
	LuaClass::LuaClass()
	{

	}

	//------------------------------------------------------------------------------------------------------
	LuaClass::LuaClass(lua_State* L)
	{

	}

	//------------------------------------------------------------------------------------------------------
	LuaClass::~LuaClass()
	{

	}

	//------------------------------------------------------------------------------------------------------
	lua_CFunction LuaClass::AccessKey(lua_State* L, const std::string& name)
	{
		lua_CFunction func = lua_functions.at(name);

		lua_pushcfunction(L, func);

		return func;
	}
}