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

namespace blowbox
{
	template<typename T>
	class LuaRegister
	{
	public:
		inline static void Register(lua_State* state, bool constructable = false)
		{
			T::RegisterFunctions(state);

			if (constructable)
			{
				lua_pushcfunction(state, LuaRegister<T>::LuaNew);
				lua_setfield(state, -2, "new");

				lua_pushvalue(state, -1);
				lua_setfield(state, -1, "__index");
				lua_setglobal(state, T::class_name());
			}
		};

		inline static int LuaNew(lua_State* state)
		{
			T* p = new T(state);
			
			typedef struct { T* pT; } userDataType;

			userDataType** udata = (userDataType**)lua_newuserdata(state, sizeof(userDataType*));
			
			luaL_getmetatable(state, T::class_name());
			lua_setmetatable(state, -2);
			return 1;
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