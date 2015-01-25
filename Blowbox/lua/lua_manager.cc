#include "lua_manager.h"

#include "lua_class.h"
#include "../content/content_manager.h"
#include "../geom/quad.h"

#include <sstream>

namespace blowbox
{
	LuaManager::LuaManager()
	{
		state_ = lua_open();
		luaopen_base(state_);
		luaopen_io(state_);
		luaopen_string(state_);
		luaopen_math(state_);
		luaopen_table(state_);
		luaopen_os(state_);
		luaopen_bit(state_);
		luaopen_ffi(state_);
		luaopen_jit(state_);
		luaopen_debug(state_);

		LuaRegister<ContentManager>::Register(state_);
		LuaRegister<Quad>::Register(state_, true);

	};

	LuaManager::~LuaManager()
	{
		lua_close(state_);
	};

	LuaManager* LuaManager::Instance()
	{
		static SharedPtr<LuaManager> ptr(new LuaManager());
		return ptr.get();
	}

	void LuaManager::LoadScript(std::string path, bool reloading)
	{
		if (luaL_dofile(state_, path.c_str()))
		{
			BLOW_BREAK(lua_tostring(state_, -1));
		}

		if (!reloading)
		{
			FileWatch::Instance()->Add(path, FileType::Script);
		}
	}

	lua_State* LuaManager::GetState()
	{
		return state_;
	}

	int LuaManager::LuaRequire(lua_State *L) 
	{
		const char* path = luaL_checkstring(L, 1);
		//LuaManager::Instance()->LoadScript(path);

		return 0;
	}

	int LuaManager::LuaNew(lua_State* state)
	{
		if (lua_istable(state, -1))
		{
			
		}

		return 0;
	}
}