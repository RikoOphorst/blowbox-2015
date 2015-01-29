#pragma once

#include "../lua/lua_manager.h"
#include "../lua/lua_class.h"
#include "d3d11_display_device.h"

namespace blowbox
{
	struct Resolution {
		Resolution(int width, int height) : w(width), h(height){}
		int w;
		int h;
	};

	class D3D11Settings : public LuaClass
	{
	public:
		D3D11Settings();
		D3D11Settings(lua_State* state);
		~D3D11Settings();

		static D3D11Settings* Instance();

		static int RegisterFunctions(lua_State* state);

		static int LuaSetFillMode(lua_State* state);
		static int LuaSetCullMode(lua_State* state);
		static int LuaSetFullscreen(lua_State* state);
		static int LuaSetVsync(lua_State* state);
		static int LuaSetBackbufferColour(lua_State* state);

		static int LuaGetCullMode(lua_State* state);
		static int LuaGetFullscreen(lua_State* state);
		static int LuaGetVsync(lua_State* state);
		static int LuaGetBackbufferColour(lua_State* state);

	private:
		Resolution resolution_;
		D3D11_FILL_MODE fillMode_;
		D3D11_CULL_MODE cullMode_;
	};
}