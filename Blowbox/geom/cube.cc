#include "cube.h"

namespace blowbox
{
	Cube::Cube()
		: vertexBuffer_(nullptr), indexBuffer_(nullptr), D3D11RenderElement()
	{
		CreateBuffers();
	};

	Cube::Cube(lua_State* state)
		: vertexBuffer_(nullptr), indexBuffer_(nullptr), D3D11RenderElement()
	{
		CreateBuffers();

		D3D11DisplayDevice::Instance()->AddElement(this);
		SetPosition(0, 0, 0);
		SetTexture("tex1.png");
		SetShader("shaders/effects.fx");
	}

	void Cube::CreateBuffers()
	{
		std::vector<Vertex> verts({
			// Front Face
			Vertex(-1.0f, -1.0f, -1.0f, 0.0f, 1.0f, 0, 0, 0, 0, 0, 0, 0, 0, 0),
			Vertex(-1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0, 0, 0, 0, 0, 0, 0, 0, 0),
			Vertex(1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 0, 0, 0, 0, 0, 0, 0, 0, 0),
			Vertex(1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 0, 0, 0, 0, 0, 0, 0, 0, 0),

			// Back Face
			Vertex(-1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 0, 0, 0, 0, 0, 0, 0, 0, 0),
			Vertex(1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 0, 0, 0, 0, 0, 0, 0, 0, 0),
			Vertex(1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0, 0, 0, 0, 0, 0, 0, 0, 0),
			Vertex(-1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0, 0, 0, 0, 0, 0, 0, 0, 0),

			// Top Face
			Vertex(-1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0, 0, 0, 0, 0, 0, 0, 0, 0),
			Vertex(-1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0, 0, 0, 0, 0, 0, 0, 0, 0),
			Vertex(1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0, 0, 0, 0, 0, 0, 0, 0, 0),
			Vertex(1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 0, 0, 0, 0, 0, 0, 0, 0, 0),

			// Bottom Face
			Vertex(-1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 0, 0, 0, 0, 0, 0, 0, 0, 0),
			Vertex(1.0f, -1.0f, -1.0f, 0.0f, 1.0f, 0, 0, 0, 0, 0, 0, 0, 0, 0),
			Vertex(1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0, 0, 0, 0, 0, 0, 0, 0, 0),
			Vertex(-1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 0, 0, 0, 0, 0, 0, 0, 0, 0),

			// Left Face
			Vertex(-1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 0, 0, 0, 0, 0, 0, 0, 0, 0),
			Vertex(-1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0, 0, 0, 0, 0, 0, 0, 0, 0),
			Vertex(-1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 0, 0, 0, 0, 0, 0, 0, 0, 0),
			Vertex(-1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 0, 0, 0, 0, 0, 0, 0, 0, 0),

			// Right Face
			Vertex(1.0f, -1.0f, -1.0f, 0.0f, 1.0f, 0, 0, 0, 0, 0, 0, 0, 0, 0),
			Vertex(1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0, 0, 0, 0, 0, 0, 0, 0, 0),
			Vertex(1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0, 0, 0, 0, 0, 0, 0, 0, 0),
			Vertex(1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 0, 0, 0, 0, 0, 0, 0, 0, 0),
		});

		std::vector<int> indices({
			// front face
			0, 1, 2,
			0, 2, 3,

			// Back Face
			4, 5, 6,
			4, 6, 7,

			// Top Face
			8, 9, 10,
			8, 10, 11,

			// Bottom Face
			12, 13, 14,
			12, 14, 15,

			// Left Face
			16, 17, 18,
			16, 18, 19,

			// Right Face
			20, 21, 22,
			20, 22, 23
		});

		vertexBuffer_ = D3D11DisplayDevice::Instance()->CreateVertexBuffer(verts);
		indexBuffer_ = D3D11DisplayDevice::Instance()->CreateIndexBuffer(indices);
	}

	int Cube::RegisterFunctions(lua_State* state)
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

	void Cube::Draw()
	{
		D3D11DisplayDevice::Instance()->SetVertexBuffer(vertexBuffer_);
		D3D11DisplayDevice::Instance()->SetIndexBuffer(indexBuffer_);
		D3D11DisplayDevice::Instance()->GetContext()->DrawIndexed(36, 0, 0);
	}

	Cube::~Cube()
	{
		D3D11DisplayDevice::Instance()->RemoveElement(this);
		
		vertexBuffer_->Release();
		indexBuffer_->Release();
	}
}