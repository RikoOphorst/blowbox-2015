#pragma once

#include "../../blowbox/d3d11/d3d11.h"

#include "../../blowbox/d3d11/d3d11_render_element.h"

namespace blowbox
{
	class Quad : public D3D11RenderElement
	{
		Quad();

		~Quad();
	};
}