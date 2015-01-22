#pragma once

#include "lua_manager.h"
#include <iostream>

namespace blowbox
{

	template<typename...Args>
	class LuaCallback
	{
	public:
		LuaCallback(const char* fnc)
		{
			fnc_ = fnc;
			table_ = "";
		};

		LuaCallback(const char* table, const char* fnc)
		{
			fnc_ = fnc;
			table_ = table;
		};

		~LuaCallback()
		{

		}

		void Call(Args...args)
		{
			int toPop = 0;
			if (table_ != "")
			{
				lua_getglobal(LuaManager::Instance()->GetState(), table_.c_str());
				lua_getfield(LuaManager::Instance()->GetState(), -1, fnc_.c_str());
				toPop = 1;
			}
			else
			{
				lua_getglobal(LuaManager::Instance()->GetState(), fnc_.c_str());
			}
			
			int nargs = LuaManager::Instance()->push_data(args...);

			int result = lua_pcall(LuaManager::Instance()->GetState(), nargs, 0, 0);

			if (result == 2)
			{
				BLOW_BREAK(lua_tostring(LuaManager::Instance()->GetState(), -1));
			}
			
			lua_pop(LuaManager::Instance()->GetState(), toPop);
		}
	private:
		std::string fnc_;
		std::string table_;
	};
}