#include "../../blowbox/d3d11/d3d11_settings.h"

#include "../../blowbox/d3d11/d3d11_render_device.h"
#include "../../blowbox/win32/window.h"
#include "../../blowbox/game.h"

namespace blowbox
{
	//------------------------------------------------------------------------------------------------------
	D3D11Settings::D3D11Settings() :
		resolution_({ 640.0f, 480.0f }),
		vsync_(false)
	{
#ifndef _DEBUG
		vsync_ = true;
#endif
	}

	//------------------------------------------------------------------------------------------------------
	D3D11Settings::D3D11Settings(lua_State* L) :
		resolution_({ 640.0f, 480.0f }),
		vsync_(false)
	{
#ifndef _DEBUG
		vsync_ = true;
#endif
	}

	//------------------------------------------------------------------------------------------------------
	D3D11Settings::~D3D11Settings()
	{

	}

	//------------------------------------------------------------------------------------------------------
	D3D11Settings* D3D11Settings::Instance()
	{
		static SharedPtr<D3D11Settings> ptr(new D3D11Settings());
		return ptr.get();
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11Settings::SetResolution(const float& width, const float& height)
	{
		resolution_.width = width;
		resolution_.height = height;

		D3D11RenderDevice::Instance()->SetResolution(width, height);
		Game::Instance()->GetWindow()->SetResolution(width, height);
	}

	//------------------------------------------------------------------------------------------------------
	const Resolution& D3D11Settings::GetResolution()
	{
		return resolution_;
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11Settings::SetVSync(const bool& vsync)
	{
		vsync_ = vsync;
	}

	//------------------------------------------------------------------------------------------------------
	const bool& D3D11Settings::GetVSync()
	{
		return vsync_;
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11Settings::LuaRegisterFunctions(lua_State* L)
	{
		luaL_Reg regist[] = {
			{ "setResolution", LuaSetResolution },
			{ "getResolution", LuaGetResolution },
			{ "setVSync", LuaSetVSync },
			{ "getVSync", LuaGetVSync },
			{ NULL, NULL }
		};

		luaL_register(L, NULL, regist);
	}

	//------------------------------------------------------------------------------------------------------
	int D3D11Settings::LuaSetResolution(lua_State* L)
	{
		D3D11Settings::Instance()->SetResolution(static_cast<float>(LuaWrapper::Instance()->Get<double>(L, -2, 1)), static_cast<float>(LuaWrapper::Instance()->Get<double>(L, -1, 2)));

		return 0;
	}

	//------------------------------------------------------------------------------------------------------
	int D3D11Settings::LuaGetResolution(lua_State* L)
	{
		return LuaWrapper::Instance()->Push(L, D3D11Settings::Instance()->GetResolution().width, D3D11Settings::Instance()->GetResolution().height);
	}

	//------------------------------------------------------------------------------------------------------
	int D3D11Settings::LuaSetVSync(lua_State* L)
	{
		D3D11Settings::Instance()->SetVSync(LuaWrapper::Instance()->Get<bool>(L, -1, 1));

		return 0;
	}

	//------------------------------------------------------------------------------------------------------
	int D3D11Settings::LuaGetVSync(lua_State* L)
	{
		return LuaWrapper::Instance()->Push(L, D3D11Settings::Instance()->GetVSync());
	}
}