#include "quad.h"

namespace blowbox
{
	Quad::Quad()
		: vertexBuffer_(nullptr), indexBuffer_(nullptr), D3D11RenderElement()
	{
		std::vector<Vertex> verts({
			Vertex(-0.5f, -0.5f, 0.0f, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0),
			Vertex(-0.5f, 0.5f, 0.0f, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
			Vertex(0.5f, 0.5f, 0.0f, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
			Vertex(0.5f, -0.5f, 0.0f, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0)
		});

		std::vector<int> indices({
			0, 1, 3, 2
		});

		vertexBuffer_ = D3D11DisplayDevice::Instance()->CreateVertexBuffer(verts);
		indexBuffer_ = D3D11DisplayDevice::Instance()->CreateIndexBuffer(indices);
	};

	void Quad::Draw()
	{
		D3D11DisplayDevice::Instance()->SetVertexBuffer(vertexBuffer_);
		D3D11DisplayDevice::Instance()->SetIndexBuffer(indexBuffer_);
		D3D11DisplayDevice::Instance()->GetContext()->DrawIndexed(4, 0, 0);
	}

	Quad::~Quad()
	{
		vertexBuffer_->Release();
		indexBuffer_->Release();
	};
}