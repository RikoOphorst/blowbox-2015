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

#define LM_STATE LuaManager::Instance()->GetState()
#define LM_GAMECALL(state, fnc) lua_getglobal(##state, "Game"); lua_getfield(##state, -1, ##fnc); lua_call(##state, 0, 0)
#define LM_CALL(state, fnc) lua_getglobal(##state, ##fnc); lua_call(##state, 0, 0)

namespace blowbox
{
	class LuaManager
	{
	public:
		LuaManager();
		~LuaManager();

		static LuaManager* Instance();

		void LoadScript(std::string path, bool reloading = false);

		lua_State* GetState();

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