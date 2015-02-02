#include "quad.h"

namespace blowbox
{
	Quad::Quad()
		: vertexBuffer_(nullptr), indexBuffer_(nullptr), D3D11RenderElement()
	{
		CreateBuffers();
		SetTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	};

	Quad::Quad(lua_State* state)
		: vertexBuffer_(nullptr), indexBuffer_(nullptr), D3D11RenderElement()
	{
		CreateBuffers();
		SetTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

		D3D11DisplayDevice::Instance()->AddElement(this);
		SetPosition(0, 0, 0);
		SetTexture("tex1.png");
		SetShader("shaders/effects.fx");
	}

	void Quad::CreateBuffers()
	{
		std::vector<Vertex> verts({
			Vertex(-0.5f, -0.5f, 0.0f, 0, 1, 0, 0, 0, 0, 0, 0),
			Vertex(-0.5f, 0.5f, 0.0f, 0, 0, 0, 0, 0, 0, 0, 0),
			Vertex(0.5f, 0.5f, 0.0f, 1, 0, 0, 0, 0, 0, 0, 0),
			Vertex(0.5f, -0.5f, 0.0f, 1, 1, 0, 0, 0, 0, 0, 0)
		});

		std::vector<int> indices({
			0, 1, 3, 2
		});

		vertexBuffer_ = D3D11DisplayDevice::Instance()->CreateVertexBuffer(verts);
		indexBuffer_ = D3D11DisplayDevice::Instance()->CreateIndexBuffer(indices);
	}

	int Quad::RegisterFunctions(lua_State* state)
	{
		luaL_Reg regist[] =
		{
			{ "getAlpha", LuaGetAlpha },
			{ "setAlpha", LuaSetAlpha },
			{ "getPosition", LuaGetPosition },
			{ "setPosition", LuaSetPosition },
			{ "getRotation", LuaGetRotation },
			{ "setRotation", LuaSetRotation },
			{ "getShader", LuaGetShader },
			{ "setShader", LuaSetShader },
			{ "getTexture", LuaGetTexture },
			{ "setTexture", LuaSetTexture },
			{ "getScale", LuaGetScale },
			{ "setScale", LuaSetScale },
			{ NULL, NULL }
		};

		LM_REGISTER(state, regist);

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
		D3D11DisplayDevice::Instance()->RemoveElement(this);
		
		vertexBuffer_->Release();
		indexBuffer_->Release();
	};
}