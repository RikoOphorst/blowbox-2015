#pragma once

#include "../../blowbox/lua/lua.h"
#include "../../blowbox/lua/lua_wrapper.h"
#include <vector>

namespace blowbox
{
	class LuaCallback
	{
	public:
		LuaCallback(std::vector<LuaValue> tree);

		~LuaCallback();

		template<typename...Args>
		void Call(lua_State* L, Args...args);
	private:
		std::vector<LuaValue> tree_;
	};

	//------------------------------------------------------------------------------------------------------
	template<typename...Args>
	inline void LuaCallback::Call(lua_State* L, Args...args)
	{
		int top = lua_gettop(L);

		for (unsigned int i = 0; i < tree_.size(); ++i)
		{
			LuaValue it = tree_.at(i);
			
			if (it.location == LUA_LOCATION::LUA_LOCATION_GLOBAL)
			{
				lua_getglobal(L, it.identifier.c_str());
			}
			
			if (it.location == LUA_LOCATION::LUA_LOCATION_FIELD)
			{
				lua_getfield(L, -1, it.identifier.c_str());
			}
		}

		int arg_count = LuaWrapper::Instance()->Push(L, args...);

		if (lua_pcall(L, arg_count, 0, 0))
		{
			BLOW_BREAK(lua_tostring(L, lua_gettop(L)));
		}

		// Clear the stack
		lua_settop(L, top);
	}
}