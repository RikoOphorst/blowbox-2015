#include "../../blowbox/elements/cube.h"

#include "../../blowbox/d3d11/d3d11_vertex_buffer.h"
#include "../../blowbox/d3d11/d3d11_render_device.h"
#include "../../blowbox/d3d11/d3d11_render_target.h"
#include "../../blowbox/d3d11/d3d11_render_queue.h"

namespace blowbox
{
	//------------------------------------------------------------------------------------------------------
	Cube::Cube() :
		D3D11RenderElement()
	{
		Create();
	}

	//------------------------------------------------------------------------------------------------------
	Cube::Cube(lua_State* L) :
		D3D11RenderElement(L)
	{
		Create();

		D3D11RenderQueue* render_queue = LuaWrapper::Instance()->ParseUserdata<D3D11RenderQueue>(L, -1);

		render_queue->Add(this);
	}

	//------------------------------------------------------------------------------------------------------
	Cube::~Cube()
	{

	}

	//------------------------------------------------------------------------------------------------------
	void Cube::Create()
	{
		vertex_buffer_ = new D3D11VertexBuffer();
		vertex_buffer_->Create(
		{
			// Front Face
			Vertex(XMFLOAT4(-1.0f, -1.0f, -1.0f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f)),
			Vertex(XMFLOAT4(-1.0f, 1.0f, -1.0f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), XMFLOAT2(0.0f, 0.0f)),
			Vertex(XMFLOAT4(1.0f, 1.0f, -1.0f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), XMFLOAT2(1.0f, 0.0f)),
			Vertex(XMFLOAT4(1.0f, -1.0f, -1.0f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), XMFLOAT2(1.0f, 1.0f)),

			// Back Face
			Vertex(XMFLOAT4(-1.0f, -1.0f, 1.0f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), XMFLOAT2(1.0f, 1.0f)),
			Vertex(XMFLOAT4(1.0f, -1.0f, 1.0f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f)),
			Vertex(XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), XMFLOAT2(0.0f, 0.0f)),
			Vertex(XMFLOAT4(-1.0f, 1.0f, 1.0f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), XMFLOAT2(1.0f, 0.0f)),

			// Top Face
			Vertex(XMFLOAT4(-1.0f, 1.0f, -1.0f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f)),
			Vertex(XMFLOAT4(-1.0f, 1.0f, 1.0f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), XMFLOAT2(0.0f, 0.0f)),
			Vertex(XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), XMFLOAT2(1.0f, 0.0f)),
			Vertex(XMFLOAT4(1.0f, 1.0f, -1.0f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), XMFLOAT2(1.0f, 1.0f)),

			// Bottom Face
			Vertex(XMFLOAT4(-1.0f, -1.0f, -1.0f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), XMFLOAT2(1.0f, 1.0f)),
			Vertex(XMFLOAT4(1.0f, -1.0f, -1.0f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f)),
			Vertex(XMFLOAT4(1.0f, -1.0f, 1.0f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), XMFLOAT2(0.0f, 0.0f)),
			Vertex(XMFLOAT4(-1.0f, -1.0f, 1.0f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), XMFLOAT2(1.0f, 0.0f)),

			// Left Face
			Vertex(XMFLOAT4(-1.0f, -1.0f, 1.0f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f)),
			Vertex(XMFLOAT4(-1.0f, 1.0f, 1.0f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), XMFLOAT2(0.0f, 0.0f)),
			Vertex(XMFLOAT4(-1.0f, 1.0f, -1.0f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), XMFLOAT2(1.0f, 0.0f)),
			Vertex(XMFLOAT4(-1.0f, -1.0f, -1.0f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), XMFLOAT2(1.0f, 1.0f)),

			// Right Face
			Vertex(XMFLOAT4(1.0f, -1.0f, -1.0f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f)),
			Vertex(XMFLOAT4(1.0f, 1.0f, -1.0f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), XMFLOAT2(0.0f, 0.0f)),
			Vertex(XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), XMFLOAT2(1.0f, 0.0f)),
			Vertex(XMFLOAT4(1.0f, -1.0f, 1.0f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), XMFLOAT2(1.0f, 1.0f)),
		},
		{ 
			// Front Face
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
		}, 
		D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
		BUFFER_TYPE::BUFFER_TYPE_CUBE
		);
	}

	//------------------------------------------------------------------------------------------------------
	void Cube::LuaRegisterFunctions(lua_State* L)
	{
		luaL_Reg regist[] =
		{
			{ "setPosition", LuaSetPosition },
			{ "getPosition", LuaGetPosition },
			{ "setPosition2D", LuaSetPosition2D },
			{ "getPosition2D", LuaGetPosition2D },
			{ "setX", LuaSetX },
			{ "getX", LuaGetX },
			{ "setY", LuaSetY },
			{ "getY", LuaGetY },
			{ "setZ", LuaSetZ },
			{ "getZ", LuaGetZ },
			{ "setRotation", LuaSetRotation },
			{ "getRotation", LuaGetRotation },
			{ "setRotation2D", LuaSetRotation2D },
			{ "getRotation2D", LuaGetRotation2D },
			{ "setScale", LuaSetScale },
			{ "getScale", LuaGetScale },
			{ "setScale2D", LuaSetScale2D },
			{ "getScale2D", LuaGetScale2D },
			{ "setOffset", LuaSetOffset },
			{ "getOffset", LuaGetOffset },
			{ "setOffset2D", LuaSetOffset2D },
			{ "getOffset2D", LuaGetOffset2D },
			{ "setAlpha", LuaSetAlpha },
			{ "getAlpha", LuaGetAlpha },
			{ "setTexture", LuaSetTexture },
			{ "getTexture", LuaGetTexture },
			{ "setShader", LuaSetShader },
			{ "getShader", LuaGetShader },
			{ "setFiltering", LuaSetFiltering },
			{ "getFiltering", LuaGetFiltering },
			{ "setBlend", LuaSetBlend },
			{ "getBlend", LuaGetBlend },
			{ NULL, NULL }
		};

		luaL_register(L, NULL, regist);
	}
}