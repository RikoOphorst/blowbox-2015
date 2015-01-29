#include "d3d11_settings.h"

namespace blowbox
{
	D3D11Settings::D3D11Settings()
		: resolution_(640, 480)
	{

	}

	D3D11Settings::D3D11Settings(lua_State* state)
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
}