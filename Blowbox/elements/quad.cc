#include "../../blowbox/elements/quad.h"

#include "../../blowbox/d3d11/d3d11_vertex_buffer.h"

namespace blowbox
{
	Quad::Quad()
	{
		vertex_buffer_ = new D3D11VertexBuffer();
		vertex_buffer_->Create(
			{
				{ XMFLOAT4(-0.5f, -0.5f, 0.0f, 1.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f), XMFLOAT2(0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 1.0f) },
				{ XMFLOAT4(-0.5f, 0.5f, 0.0f, 1.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f), XMFLOAT2(0.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 1.0f) },
				{ XMFLOAT4(0.5f, -0.5f, 0.0f, 1.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f), XMFLOAT2(1.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 1.0f) },
				{ XMFLOAT4(0.5f, 0.5f, 0.0f, 1.0f), XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f), XMFLOAT2(1.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 1.0f) }
			},
			{ 0, 1, 2, 3 },
			D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP,
			BUFFER_TYPE::BUFFER_TYPE_QUAD
		);
	}

	Quad::~Quad()
	{
		
	}
}