#pragma once

#include "../../blowbox/lua/lua_wrapper.h"
#include "../../blowbox/lua/lua_register.h"

namespace blowbox
{
	class LuaClass
	{
	public:
		LuaClass();
		~LuaClass();

		template<typename T>
		static int LuaConstructor(lua_State* L);

		template <typename T>
		static int LuaDestructor(lua_State* L);

		static void LuaRegisterFunctions(lua_State* L);
	protected:
		
	};

	//------------------------------------------------------------------------------------------------------
	template<typename T>
	inline int LuaClass::LuaConstructor(lua_State* L)
	{
		T* ptr = new T(L);

		typedef struct { T* pT; } userDataType;

		luaL_getmetatable(L, "hurdur");
		int mt = lua_gettop(L);

		lua_pushstring(L, "userdata");

		lua_gettable(L, mt);

		if (lua_isnil(L, -1))
		{
			lua_pop(L, 1);

			lua_checkstack(L, 3);

			lua_newtable(L);

			lua_pushvalue(L, -1);

			lua_setmetatable(L, -2);

			lua_pushliteral(L, "__mode");

			lua_pushstring(L, "v");

			lua_settable(L, -3);

			lua_pushstring(L, "userdata");

			lua_pushvalue(L, -2);
			lua_settable(L, mt);
		}

		lua_pushlightuserdata(L, ptr);
		lua_gettable(L, -2);

		if (lua_isnil(L, -1))
		{
			lua_pop(L, 1);
			lua_checkstack(L, 3);
			userDataType* udata = (userDataType*)lua_newuserdata(L, sizeof(userDataType*));
			lua_pushlightuserdata(L, ptr);
			lua_pushvalue(L, -2);
			lua_settable(L, -4);

			udata->pT = ptr;

			lua_pushvalue(L, mt);
			lua_setmetatable(L, -2);
		}

		lua_replace(L, mt);

		lua_settop(L, mt);
		return 1;
	}

	//------------------------------------------------------------------------------------------------------
	template<typename T>
	inline int LuaClass::LuaDestructor(lua_State* L)
	{
		T* ptr = LuaWrapper::Instance()->ParseUserdata<T>(L, 1);

		delete ptr;
		ptr = nullptr;

		return 0;
	}
}