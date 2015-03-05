#pragma once

#include "../../blowbox/d3d11/d3d11.h"

#include "../../blowbox/d3d11/d3d11_render_element.h"
#include "../../blowbox/lua/lua_class.h"

namespace blowbox
{
	class Quad : public D3D11RenderElement, public LuaClass
	{
	public:
		Quad();

		Quad(lua_State* L);

		~Quad();

		static void LuaRegisterFunctions(lua_State* state);

		static int LuaSetPosition(lua_State* L);
	};
}