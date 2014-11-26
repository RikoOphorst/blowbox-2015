#pragma once

#include "../d3d11/d3d11_display_device.h"
#include "../d3d11/d3d11_render_element.h"

namespace blowbox
{
	class Cube : public D3D11RenderElement
	{
	public:
		Cube();

		void Draw();

		virtual ~Cube();
	private:
		ID3D11Buffer* vertexBuffer_;
		ID3D11Buffer* indexBuffer_;
		bool tex_;
	};
}