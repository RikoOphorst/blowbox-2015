#include "../../blowbox/elements/quad.h"

#include "../../blowbox/d3d11/d3d11_vertex_buffer.h"
#include "../../blowbox/d3d11/d3d11_render_device.h"
#include "../../blowbox/d3d11/d3d11_render_target.h"
#include "../../blowbox/d3d11/d3d11_render_queue.h"

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

	Quad::Quad(lua_State* L)
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

		D3D11RenderDevice::Instance()->GetRenderTarget("hurdur")->GetQueue()->Add(this);

		SetPosition(0.0f, 0.0f, 0.0f);
		SetScale(50, 50, 1);
		SetShader("shaders/base.fx");
	}

	Quad::~Quad()
	{
		
	}

	void Quad::LuaRegisterFunctions(lua_State* L)
	{
		luaL_Reg regist[] =
		{
			{ "setPosition", LuaSetPosition },
			{ NULL, NULL }
		};

		luaL_register(L, NULL, regist);
	}

	int Quad::LuaSetPosition(lua_State* L)
	{
		Quad* self = LuaWrapper::Instance()->ParseUserdata<Quad>(L, 1);
		
		double x = LuaWrapper::Instance()->Get<double>(L, -1, true);
		double y = LuaWrapper::Instance()->Get<double>(L, -2, true);
		double z = LuaWrapper::Instance()->Get<double>(L, -3, true);

		self->SetPosition(x, y, z);

		return 0;
	}
}