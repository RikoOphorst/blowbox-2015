#include "../../blowbox/elements/quad.h"

#include "../../blowbox/d3d11/d3d11_vertex_buffer.h"
#include "../../blowbox/d3d11/d3d11_render_device.h"
#include "../../blowbox/d3d11/d3d11_render_target.h"
#include "../../blowbox/d3d11/d3d11_render_queue.h"
#include "../../blowbox/console/console.h"

namespace blowbox
{
	//------------------------------------------------------------------------------------------------------
	Quad::Quad() :
		D3D11RenderElement()
	{
		Create();
	}

	//------------------------------------------------------------------------------------------------------
	Quad::Quad(lua_State* L) :
		D3D11RenderElement(L)
	{
		Create();

		LuaWrapper::Instance()->Dump(L, "HURDUR WHATRS ON THE STAKCKK");

		render_queue_ = LuaWrapper::Instance()->ParseUserdata<D3D11RenderQueue>(L, 1);

		render_queue_->Add(this);
	}

	//------------------------------------------------------------------------------------------------------
	Quad::~Quad()
	{
		
	}

	//------------------------------------------------------------------------------------------------------
	void Quad::Create()
	{
		vertex_buffer_ = new D3D11VertexBuffer();
		vertex_buffer_->Create(
			{
				Vertex(XMFLOAT4(-0.5f, -0.5f, 0.0f, 1.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f), XMFLOAT2(0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 1.0f)),
				Vertex(XMFLOAT4(-0.5f, 0.5f, 0.0f, 1.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f), XMFLOAT2(0.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 1.0f)),
				Vertex(XMFLOAT4(0.5f, -0.5f, 0.0f, 1.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f), XMFLOAT2(1.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 1.0f)),
				Vertex(XMFLOAT4(0.5f, 0.5f, 0.0f, 1.0f), XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f), XMFLOAT2(1.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 1.0f))
			},
			{ 0, 1, 2, 3 },
			D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP,
			BUFFER_TYPE::BUFFER_TYPE_QUAD
		);
	}

	//------------------------------------------------------------------------------------------------------
	void Quad::LuaRegisterFunctions(lua_State* L)
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