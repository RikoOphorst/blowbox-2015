#pragma once

#include "../d3d11/d3d11_display_device.h"
#include "../d3d11/d3d11_render_element.h"
#include "../lua/lua_manager.h"
#include "../lua/lua_class.h"

namespace blowbox
{
	class Line
	{
	public:
		Line();
		Line(lua_State* state);

		static Line* Instance();

		virtual ~Line();

		static int RegisterFunctions(lua_State* state);

		static int LuaDraw(lua_State* state);

		void PushVertex(Vertex vert);

		void Draw();

		LM_NAME("Line");
	private:
		ID3D11Buffer* vertexBuffer_;
		std::vector<Vertex> lines_;
	};
}