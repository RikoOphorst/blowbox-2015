#include "lua_manager.h"

#define LM_STATE LuaManager::Instance()->GetState()
#define LM_GAMECALL(state, fnc) lua_getglobal(##state, "Game"); lua_getfield(##state, -1, ##fnc); lua_call(##state, 0, 0)
#define LM_CALL(state, fnc) lua_getglobal(##state, ##fnc); lua_call(##state, 0, 0)

namespace blowbox
{
	LuaManager::LuaManager() 
	{
		state_ = lua_open();
		luaopen_base(state_);
		luaopen_io(state_);
		luaopen_string(state_);
		luaopen_math(state_);
	};

	LuaManager::~LuaManager() 
	{

	};

	LuaManager* LuaManager::Instance()
	{
		static SharedPtr<LuaManager> ptr(new LuaManager());
		return ptr.get();
	}

	void LuaManager::MakeError(std::string err)
	{
		std::cout << "Lua error: " << err << std::endl;
	}

	void LuaManager::LoadScript(std::string path, bool reloading)
	{
		if (luaL_dofile(state_, path.c_str()))
			MakeError(lua_tostring(state_, -1));

		LM_GAMECALL(state_, "Init");
		LM_GAMECALL(state_, "Update");
		LM_GAMECALL(state_, "Render");

		LM_CALL(state_, "hurdur");

		if (!reloading)
		{
			FileWatch::Instance()->Add(path, FileType::Script);
		}
	}

	lua_State* LuaManager::GetState()
	{
		return state_;
	}
}