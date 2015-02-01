#include "d3d11_settings.h"

namespace blowbox
{
	D3D11Settings::D3D11Settings()
		: resolution_(640, 480)
	{

	}

	D3D11Settings::D3D11Settings(lua_State* state)
		: resolution_(640, 480)
	{

	}

	D3D11Settings::~D3D11Settings()
	{

	}

	D3D11Settings* D3D11Settings::Instance()
	{
		static SharedPtr<D3D11Settings> ptr(new D3D11Settings());
		return ptr.get();
	}

	int D3D11Settings::RegisterFunctions(lua_State* state)
	{
		luaL_Reg regist[] =
		{
			{ "getFullscreen", LuaGetFullscreen },
			{ "setFullscreen", LuaSetFullscreen },
			{ "setFillMode", LuaSetFillMode },
			{ "getFillMode", LuaGetFillMode },
			{ "setCullMode", LuaSetCullMode },
			{ "getCullMode", LuaGetCullMode },
			{ "setVsync", LuaSetVsync },
			{ "getVsync", LuaGetVsync },
			{ NULL, NULL }
		};

		LM_REGISTER(state, regist);

		return 0;
	}

	int D3D11Settings::LuaGetFullscreen(lua_State* state)
	{
		BOOL fullscreen;
		D3D11DisplayDevice::Instance()->GetSwapChain()->GetFullscreenState(&fullscreen, NULL);

		LuaManager::PushValue((fullscreen == TRUE));
		return 1;
	}

	int D3D11Settings::LuaSetFullscreen(lua_State* state)
	{
		D3D11DisplayDevice::Instance()->GetSwapChain()->SetFullscreenState(LuaManager::GetValue<int>(0), NULL);
		return 0;
	}

	int D3D11Settings::LuaGetFillMode(lua_State* state)
	{
		LuaManager::PushValue(D3D11DisplayDevice::Instance()->GetFillMode());
		return 1;
	}

	int D3D11Settings::LuaSetFillMode(lua_State* state)
	{
		const char* md = LuaManager::GetValue<const char *>(0);
		D3D11_FILL_MODE mode;

		if (strcmp(md, "wireframe") == 0) { mode = D3D11_FILL_MODE::D3D11_FILL_WIREFRAME; }
		if (strcmp(md, "solid") == 0) { mode = D3D11_FILL_MODE::D3D11_FILL_SOLID; }

		D3D11DisplayDevice::Instance()->SetRasterizerState(mode, D3D11DisplayDevice::Instance()->GetCullMode());

		return 0;
	}

	int D3D11Settings::LuaGetCullMode(lua_State* state)
	{
		LuaManager::PushValue(D3D11DisplayDevice::Instance()->GetFillMode());
		return 1;
	}

	int D3D11Settings::LuaSetCullMode(lua_State* state)
	{
		const char* md = LuaManager::GetValue<const char *>(0);
		D3D11_CULL_MODE mode;

		if (strcmp(md, "back") == 0) { mode = D3D11_CULL_MODE::D3D11_CULL_BACK; }
		if (strcmp(md, "front") == 0) { mode = D3D11_CULL_MODE::D3D11_CULL_FRONT; }
		if (strcmp(md, "none") == 0) { mode = D3D11_CULL_MODE::D3D11_CULL_NONE; }

		D3D11DisplayDevice::Instance()->SetRasterizerState(D3D11DisplayDevice::Instance()->GetFillMode(), mode);

		return 0;
	}

	int D3D11Settings::LuaGetVsync(lua_State* state)
	{
		LuaManager::PushValue((D3D11DisplayDevice::Instance()->GetVsync() == TRUE));
		return 1;
	}

	int D3D11Settings::LuaSetVsync(lua_State* state)
	{
		D3D11DisplayDevice::Instance()->SetVsync(LuaManager::GetValue<int>(0));
		return 0;
	}
}