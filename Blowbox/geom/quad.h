#pragma once

#include "../d3d11/d3d11_display_device.h"
#include "../d3d11/d3d11_render_element.h"

namespace blowbox
{
	class Quad : public D3D11RenderElement
	{
	public:
		Quad();
		Quad(lua_State* state);

		static int CleanUp(lua_State* state);

		void Draw();

		static int RegisterFunctions(lua_State* state);
		virtual ~Quad();

		LM_NAME("Quad");
	private:
		ID3D11Buffer* vertexBuffer_;
		ID3D11Buffer* indexBuffer_;
	};
}