#pragma once

extern "C"
{
	#include <lua.h>
	#include <lauxlib.h>
	#include <lualib.h>
}

#include "../memory/shared_ptr.h"
#include "../win32/file_watch.h"
#include "lua_callback.h"
#include "lua_class.h"

#define LM_STATE LuaManager::Instance()->GetState()
#define LM_GAMECALL(state, fnc) lua_getglobal(##state, "Game"); lua_getfield(##state, -1, ##fnc); lua_call(##state, 0, 0)
#define LM_METHODCALL(state, table, fnc) lua_getglobal(##state, ##table); lua_getfield(##state, -1, ##fnc); lua_call(##state, 0, 0)
#define LM_CALL(state, fnc) lua_getglobal(##state, ##fnc); lua_call(##state, 0, 0)
#define LM_FUNCTION(state, fnc, name) lua_pushcfunction(##state, ##fnc); lua_setglobal(##state, ##name);
#define LM_METHOD(state, fnc, table, name) lua_getglobal(##state, ##table); lua_pushcfunction(##state, ##fnc); lua_setfield(##state, -2, ##name)
#define LM_GETSELF(type) struct userDataType { type* pT; } *ud; ud = (userDataType*)(lua_touserdata(state, 1)); type* self = ud->pT;

namespace blowbox
{
	template<typename T>
	class LuaRegister
	{
	public:
		inline static void Register(lua_State* state, bool constructable = false)
		{
			lua_newtable(state);
			int methods = lua_gettop(state);

			if (constructable)
			{
				luaL_newmetatable(state, T::class_name());
				int mt = lua_gettop(state);

				lua_pushvalue(state, methods);
				lua_setfield(state, LUA_GLOBALSINDEX, T::class_name());

				lua_pushvalue(state, methods);
				lua_pushvalue(state, methods);

				lua_setfield(state, mt, "__index");

				lua_pushcfunction(state, LuaRegister<T>::LuaGC);
				lua_setfield(state, mt, "__gc");

				lua_newtable(state);

				lua_pushcfunction(state, LuaRegister<T>::LuaNew);
				lua_pushvalue(state, -1);
				lua_setfield(state, methods, "new");
				lua_setfield(state, -3, "__call");
				lua_setmetatable(state, methods);

				lua_pushvalue(state, methods);

				T::RegisterFunctions(state);

				lua_pop(state, 3);
			}
			else
			{
				T::RegisterFunctions(state);
				lua_setfield(state, LUA_GLOBALSINDEX, T::class_name());
			}
		};

		inline static int LuaNew(lua_State* state)
		{
			T* p = new T(state);
			
			typedef struct { T* pT; } userDataType;

			luaL_getmetatable(state, T::class_name());
			int mt = lua_gettop(state);

			lua_pushstring(state, "userdata");

			lua_gettable(state, mt);

			if (lua_isnil(state, -1))
			{
				lua_pop(state, 1);

				lua_checkstack(state, 3);

				lua_newtable(state);

				lua_pushvalue(state, -1);

				lua_setmetatable(state, -2);

				lua_pushliteral(state, "__mode");

				lua_pushstring(state, "v");

				lua_settable(state, -3);

				lua_pushstring(state, "userdata");

				lua_pushvalue(state, -2);

				lua_settable(state, mt);
			}

			lua_pushlightuserdata(state, p);
			lua_gettable(state, -2);

			if (lua_isnil(state, -1))
			{
				lua_pop(state, 1);
				lua_checkstack(state, 3);
				userDataType* udata = (userDataType*)lua_newuserdata(state, sizeof(userDataType*));
				lua_pushlightuserdata(state, p);
				lua_pushvalue(state, -2);
				lua_settable(state, -4);

				udata->pT = p;

				lua_pushvalue(state, mt);
				lua_setmetatable(state, -2);
			}

			lua_replace(state, mt);

			lua_settop(state, mt);
			return 1;
		}

		inline static int LuaGC(lua_State* state)
		{
			LM_GETSELF(T);

			delete self;
			self = NULL;

			return 0;
		}
	};

	class LuaManager
	{
	public:
		LuaManager();
		~LuaManager();

		static LuaManager* Instance();

		void LoadScript(std::string path, bool reloading = false);

		static int LuaRequire(lua_State* state);

		static int LuaNew(lua_State* state);

		lua_State* GetState();

		inline int push_data()
		{
			return 0;
		}

		template<typename T>
		inline int push_data(T first)
		{
			push(first);

			return 1;
		}


		template<typename T, typename ... Args>
		inline int push_data(T first, Args ... others)
		{
			push(first);

			return push_data(others...) + 1;
		}

		template <typename T>
		void push(T thing);
	private:
		lua_State* state_;
	};

	template<>
	inline void LuaManager::push<int>(int num)
	{
		lua_pushnumber(LM_STATE, num);
	}

	template<>
	inline void LuaManager::push<double>(double num)
	{
		lua_pushnumber(LM_STATE, num);
	}
}