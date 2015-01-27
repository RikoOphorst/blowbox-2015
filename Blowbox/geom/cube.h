#pragma once

#include "../d3d11/d3d11_display_device.h"
#include "../d3d11/d3d11_render_element.h"
#include "../lua/lua_manager.h"
#include "../lua/lua_class.h"

namespace blowbox
{
	class Cube : public D3D11RenderElement
	{
	public:
		Cube();
		Cube(lua_State* state);

		void CreateBuffers();

		void Draw();

		static int RegisterFunctions(lua_State* state);
		virtual ~Cube();

		LM_NAME("Cube");
	private:
		ID3D11Buffer* vertexBuffer_;
		ID3D11Buffer* indexBuffer_;
		bool tex_;
	};
}