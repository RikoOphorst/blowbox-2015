#pragma once

#include "lua_manager.h"

#define LM_CLASS_CONSTRUCT(state, type, name) \
	type** udata = (type**)lua_newuserdata(state, sizeof(type*)); \
	*udata = new type(state); \
	luaL_getmetatable(state, ##name); \
	lua_setmetatable(state, -2);
#define LM_SINGLETON_REGISTER(state, funcregister, identifier, name) \
	luaL_newmetatable(state, ##identifier); \
	luaL_register(state, NULL, funcregister); \
	lua_pushvalue(state, -1); \
	lua_setfield(state, -1, "__index"); \
	lua_setglobal(state, ##name);
#define LM_INSTANCE_REGISTER(state, funcregister, type) \
	luaL_newmetatable(state, type::class_name()); \
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