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

	Quad::Quad(lua_State* state)
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

		D3D11DisplayDevice::Instance()->AddElement(this);
		SetPosition(-50.0f, -20.0f, 0);
		SetTexture("tex1.png");
		SetShader("shaders/anotherFile.fx");
	}

	int Quad::RegisterFunctions(lua_State* state)
	{
		luaL_Reg regist[] =
		{
			{ "bleh", Bleh },
			{ NULL, NULL }
		};

		LM_INSTANCE_REGISTER(state, regist, Quad);

		return 0;
	}

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