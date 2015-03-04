#include "../../blowbox/lua/lua_class.h"

namespace blowbox
{
	//------------------------------------------------------------------------------------------------------
	LuaClass::LuaClass()
	{

	}

	//------------------------------------------------------------------------------------------------------
	LuaClass::~LuaClass()
	{

	}

	//------------------------------------------------------------------------------------------------------
	template<typename T>
	int LuaClass::LuaConstructor(lua_State* L)
	{
		T* ptr = new T(L);

		typedef struct { T* pT; } userDataType;

		/*luaL_getmetatable(L, T::class_name());
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

		lua_pushlightuserdata(L, p);
		lua_gettable(L, -2);

		if (lua_isnil(L, -1))
		{
			lua_pop(L, 1);
			lua_checkstack(L, 3);
			userDataType* udata = (userDataType*)lua_newuserdata(L, sizeof(userDataType*));
			lua_pushlightuserdata(L, p);
			lua_pushvalue(L, -2);
			lua_settable(L, -4);

			udata->pT = p;

			lua_pushvalue(L, mt);
			lua_setmetatable(L, -2);
		}

		lua_replace(L, mt);

		lua_settop(L, mt);*/
		return 1;
	}

	int LuaClass::LuaDestructor(lua_State* L)
	{
		return 0;
	}
}