#include "lua_manager.h"

#include "lua_class.h"
#include "../content/content_manager.h"
#include "../input/keyboard.h"
#include "../input/mouse.h"
#include "../geom/quad.h"
#include "../geom/cube.h"
#include "../d3d11/d3d11_settings.h"
#include "../d3d11/d3d11_camera.h"
#include "lua_callback.h"
#include "lua_class.h"

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

		LM_FUNCTION(state_, LuaManager::LuaRequire, "require");

		LuaRegister<ContentManager>::Register(state_);
		LuaRegister<Keyboard>::Register(state_);
		LuaRegister<Mouse>::Register(state_);
		LuaRegister<Quad>::Register(state_, true);
		LuaRegister<Cube>::Register(state_, true);
		LuaRegister<D3D11Settings>::Register(state_);
		LuaRegister<D3D11Camera>::Register(state_);
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

	template<>
	int LuaManager::GetValue<int>(int stackIndex)
	{
		return static_cast<int>(luaL_checknumber(LM_STATE, stackIndex + 1));
	}

	template<>
	double LuaManager::GetValue<double>(int stackIndex)
	{
		return static_cast<double>(luaL_checknumber(LM_STATE, stackIndex + 1));
	}

	template<>
	float LuaManager::GetValue<float>(int stackIndex)
	{
		return static_cast<float>(luaL_checknumber(LM_STATE, stackIndex + 1));
	}

	template<>
	std::string LuaManager::GetValue<std::string>(int stackIndex)
	{
		return static_cast<std::string>(luaL_checkstring(LM_STATE, stackIndex + 1));
	}

	template<>
	const char* LuaManager::GetValue<const char*>(int stackIndex)
	{
		return static_cast<const char*>(luaL_checkstring(LM_STATE, stackIndex + 1));
	}

	template<>
	bool LuaManager::GetValue<bool>(int stackIndex)
	{
		return lua_isboolean(LM_STATE, stackIndex + 1);
	}

	int LuaManager::PushValue()
	{
		lua_pushnil(LM_STATE);
		return 1;
	}

	int LuaManager::PushValue(int value)
	{
		lua_pushnumber(LM_STATE, static_cast<lua_Number>(value));
		return 1;
	}

	int LuaManager::PushValue(double value)
	{
		lua_pushnumber(LM_STATE, static_cast<lua_Number>(value));
		return 1;
	}

	int LuaManager::PushValue(float value)
	{
		lua_pushnumber(LM_STATE, static_cast<lua_Number>(value));
		return 1;
	}

	int LuaManager::PushValue(std::string value)
	{
		lua_pushstring(LM_STATE, value.c_str());
		return 1;
	}

	int LuaManager::PushValue(const char* value)
	{
		lua_pushstring(LM_STATE, value);
		return 1;
	}

	int LuaManager::PushValue(bool value)
	{
		lua_pushboolean(LM_STATE, value);
		return 1;
	}

	int LuaManager::LuaRequire(lua_State *L) 
	{
		const char* path = luaL_checkstring(L, 1);
		LuaManager::Instance()->LoadScript(path);

		return 0;
	}
}