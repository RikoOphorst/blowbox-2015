#include "../../blowbox/elements/line.h"

#include "../../blowbox/d3d11/d3d11_render_device.h"
#include "../../blowbox/d3d11/d3d11_constant_buffer.h"
#include "../../blowbox/content/content_manager.h"

namespace blowbox
{
	//------------------------------------------------------------------------------------------------------
	Line::Line()
	{
		if (!ContentManager::Instance()->IsShaderLoaded(BASE_LINE_SHADER))
		{
			ContentManager::Instance()->LoadShader(BASE_LINE_SHADER);
		}
		shader_ = ContentManager::Instance()->GetShader(BASE_LINE_SHADER);
		buffer_ = new D3D11VertexBuffer();
	}

	//------------------------------------------------------------------------------------------------------
	Line::Line(lua_State* L)
	{

	}

	//------------------------------------------------------------------------------------------------------
	Line::~Line()
	{

	}

	//------------------------------------------------------------------------------------------------------
	Line* Line::Instance()
	{
		static SharedPtr<Line> ptr(new Line());
		return ptr.get();
	}

	//------------------------------------------------------------------------------------------------------
	void Line::Push(Vertex vert)
	{
		lines_.push_back(vert);
	}

	//------------------------------------------------------------------------------------------------------
	void Line::SetShader(const std::string& path)
	{
		shader_ = ContentManager::Instance()->GetShader(path);
	}

	//------------------------------------------------------------------------------------------------------
	D3D11Shader* Line::GetShader()
	{
		return shader_;
	}

	//------------------------------------------------------------------------------------------------------
	void Line::Draw(ID3D11DeviceContext* context)
	{
		if (lines_.size() > 0)
		{
			buffer_->Create(lines_, D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_LINELIST, BUFFER_TYPE::BUFFER_TYPE_UNKNOWN);
			buffer_->Set(context);
			shader_->Set(context);

			D3D11RenderDevice::Instance()->GetObjectBuffer()->Map(context, {
				XMMatrixIdentity(),
				1
			});
			D3D11RenderDevice::Instance()->GetObjectBuffer()->Set(context, 1);

			buffer_->Draw(context);
			lines_.clear();
		}
	}
	
	//------------------------------------------------------------------------------------------------------
	void Line::LuaRegisterFunctions(lua_State* L)
	{
		luaL_Reg regist[] = {
			{ "draw", LuaDraw },
			{ "setShader", LuaSetShader },
			{ "getShader", LuaGetShader },
			{ NULL, NULL }
		};

		luaL_register(L, NULL, regist);
	}

	//------------------------------------------------------------------------------------------------------
	int Line::LuaDraw(lua_State* L)
	{
		Vertex vert;

		vert.normal.x = 0;
		vert.normal.y = 0;
		vert.normal.z = 0;

		vert.tex_coords.x = 0;
		vert.tex_coords.y = 0;

		vert.position.x = LuaWrapper::Instance()->Get<float>(L, 1);
		vert.position.y = LuaWrapper::Instance()->Get<float>(L, 2);
		vert.position.z = LuaWrapper::Instance()->Get<float>(L, 3);
		vert.position.w = 1;

		vert.color.x = LuaWrapper::Instance()->Get<float>(L, 4);
		vert.color.y = LuaWrapper::Instance()->Get<float>(L, 5);
		vert.color.z = LuaWrapper::Instance()->Get<float>(L, 6);
		vert.color.w = LuaWrapper::Instance()->Get<float>(L, 7);

		Line::Instance()->Push(vert);

		vert.position.x = LuaWrapper::Instance()->Get<float>(L, 8);
		vert.position.y = LuaWrapper::Instance()->Get<float>(L, 9);
		vert.position.z = LuaWrapper::Instance()->Get<float>(L, 10);
		vert.position.w = 1;

		vert.color.x = LuaWrapper::Instance()->Get<float>(L, 11);
		vert.color.y = LuaWrapper::Instance()->Get<float>(L, 12);
		vert.color.z = LuaWrapper::Instance()->Get<float>(L, 13);
		vert.color.w = LuaWrapper::Instance()->Get<float>(L, 14);

		Line::Instance()->Push(vert);

		return 0;
	}

	//------------------------------------------------------------------------------------------------------
	int Line::LuaSetShader(lua_State* L)
	{
		Line::Instance()->SetShader(LuaWrapper::Instance()->Get<std::string>(L, 1));

		return 0;
	}

	//------------------------------------------------------------------------------------------------------
	int Line::LuaGetShader(lua_State* L)
	{
		return LuaWrapper::Instance()->Push(L, "");
	}
}