#pragma once

#include "../../blowbox/lua/lua_wrapper.h"
#include "../../blowbox/lua/lua_register.h"

#undef GetClassName

namespace blowbox
{
	class LuaClass
	{
	public:
		LuaClass() {};
		~LuaClass() {};

		template<typename T>
		static int LuaConstructor(lua_State* L);
		static int LuaDestructor(lua_State* L);

		static int GetClassName();
	protected:
		
	};
}