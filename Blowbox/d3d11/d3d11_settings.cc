#include "../../blowbox/d3d11/d3d11_settings.h"

namespace blowbox
{
	//------------------------------------------------------------------------------------------------------
	D3D11Settings::D3D11Settings() :
		resolution_({ 640.0f, 480.0f })
	{

	}

	//------------------------------------------------------------------------------------------------------
	D3D11Settings::D3D11Settings(lua_State* L) :
		resolution_({ 640.0f, 480.0f })
	{

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
		resolution_.height = width;
		resolution_.width = height;
	}

	//------------------------------------------------------------------------------------------------------
	const Resolution& D3D11Settings::GetResolution()
	{
		return resolution_;
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11Settings::LuaRegisterFunctions(lua_State* L)
	{
		luaL_Reg regist[] = {
			{ "setResolution", LuaSetResolution },
			{ "getResolution", LuaGetResolution },
			{ NULL, NULL }
		};

		luaL_register(L, NULL, regist);
	}

	//------------------------------------------------------------------------------------------------------
	int D3D11Settings::LuaSetResolution(lua_State* L)
	{
		D3D11Settings::Instance()->SetResolution(static_cast<float>(LuaWrapper::Instance()->Get<double>(L, -2)), static_cast<float>(LuaWrapper::Instance()->Get<double>(L, -1)));

		return 0;
	}

	//------------------------------------------------------------------------------------------------------
	int D3D11Settings::LuaGetResolution(lua_State* L)
	{
		return LuaWrapper::Instance()->Push(L, D3D11Settings::Instance()->GetResolution().width, D3D11Settings::Instance()->GetResolution().height);
	}
}