#pragma once

#include "lua_manager.h"

#define LM_CLASS_CONSTRUCT(state, type, name) \
	type** udata = (type**)lua_newuserdata(state, sizeof(type*)); \
	*udata = new type(state); \
	luaL_getmetatable(state, ##name); \
	lua_setmetatable(state, -2);
#define LM_REGISTER(state, funcregister) \
	luaL_register(state, NULL, funcregister); 
#define LM_NAME(name) static const char* class_name(){ return ##name; }

namespace blowbox
{
	class LuaClass
	{
	public:
		LuaClass(){};
		~LuaClass(){};

		static int RegisterFunctions(lua_State* state);
		static const char* class_name();
	private:
	};
}