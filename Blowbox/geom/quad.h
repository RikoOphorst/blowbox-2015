#pragma once

#include "../d3d11/d3d11_display_device.h"
#include "../d3d11/d3d11_render_element.h"

namespace blowbox
{
	class Quad : public D3D11RenderElement, public LuaClass
	{
	public:
		Quad();
		Quad(lua_State* state);

		static int Bleh(lua_State* state){
			std::cout << "dja moedahs toeltip" << std::endl; return 0;
		}

		void Draw();

		static int RegisterFunctions(lua_State* state);
		virtual ~Quad();

		LM_NAME("Quad");
	private:
		ID3D11Buffer* vertexBuffer_;
		ID3D11Buffer* indexBuffer_;
	};
}