#include "../../blowbox/lua/lua_state.h"

namespace blowbox
{
	//------------------------------------------------------------------------------------------------------
	LuaState::LuaState()
	{
		L_ = lua_open();
		OpenLibs();

		lua_settop(L_, 0);
	}

	//------------------------------------------------------------------------------------------------------
	LuaState::~LuaState()
	{
		lua_close(L_);
	}

	//------------------------------------------------------------------------------------------------------
	LuaState* LuaState::Instance()
	{
		static SharedPtr<LuaState> ptr(new LuaState());
		return ptr.get();
	}

	//------------------------------------------------------------------------------------------------------
	void LuaState::OpenLibs()
	{
		luaopen_base(L_);
		luaopen_io(L_);
		luaopen_string(L_);
		luaopen_math(L_);
		luaopen_table(L_);
		luaopen_os(L_);
		luaopen_bit(L_);
		luaopen_ffi(L_);
		luaopen_jit(L_);
		luaopen_debug(L_);
	}

	//------------------------------------------------------------------------------------------------------
	lua_State* LuaState::Get()
	{
		return L_;
	}
}