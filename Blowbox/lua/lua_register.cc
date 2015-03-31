#include "../../blowbox/lua/lua_register.h"

namespace blowbox
{
	//------------------------------------------------------------------------------------------------------
	LuaRegister::LuaRegister()
	{

	}

	//------------------------------------------------------------------------------------------------------
	LuaRegister::~LuaRegister()
	{

	}

	//------------------------------------------------------------------------------------------------------
	LuaRegister* LuaRegister::Instance()
	{
		static SharedPtr<LuaRegister> ptr(new LuaRegister());
		return ptr.get();
	}

	//------------------------------------------------------------------------------------------------------
	void LuaRegister::RegisterFunction(lua_State* L, lua_CFunction function, const std::string& name)
	{
		// Push the cfunction on the stack
		lua_pushcfunction(L, function);
		lua_setfield(L, LUA_GLOBALSINDEX, name.c_str());
	}

	//------------------------------------------------------------------------------------------------------
	void LuaRegister::RegisterFunction(lua_State* L, lua_CFunction function, const std::string& name, const int& index)
	{
		// Push the cfunction on the stack
		lua_pushcfunction(L, function);
		
		if (!lua_istable(L, index))
		{
			BLOW_BREAK("Given index on the stack is not a table, could not register the singleton");
		}
		else
		{
			lua_setfield(L, index, name.c_str());
		}
	}
}