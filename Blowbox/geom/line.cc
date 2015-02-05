#include "line.h"

#include "../content/content_manager.h"

namespace blowbox
{
	Line::Line()
		: vertexBuffer_(nullptr)
	{
		
	}

	Line::Line(lua_State* state)
		: vertexBuffer_(nullptr)
	{
		
	}

	Line* Line::Instance()
	{
		static SharedPtr<Line> line(new Line());
		return line.get();
	}

	int Line::RegisterFunctions(lua_State* state)
	{
		luaL_Reg regist[] =
		{
			{ "draw", LuaDraw },
			{ NULL, NULL }
		};

		LM_REGISTER(state, regist);

		return 0;
	}

	void Line::PushVertex(Vertex vert)
	{
		lines_.push_back(vert);
	}

	int Line::LuaDraw(lua_State* state)
	{
		Vertex vert;

		vert.normal.x = 0;
		vert.normal.y = 0;
		vert.normal.z = 0;

		vert.color.w = 1;

		vert.texCoord.x = 0;
		vert.texCoord.y = 0;

		vert.pos.x = LuaManager::GetValue<float>(0);
		vert.pos.y = LuaManager::GetValue<float>(1);
		vert.pos.z = LuaManager::GetValue<float>(2);
		vert.pos.w = 1;

		vert.color.x = LuaManager::GetValue<float>(3);
		vert.color.y = LuaManager::GetValue<float>(4);
		vert.color.z = LuaManager::GetValue<float>(5);

		Line::Instance()->PushVertex(vert);

		vert.pos.x = LuaManager::GetValue<float>(6);
		vert.pos.y = LuaManager::GetValue<float>(7);
		vert.pos.z = LuaManager::GetValue<float>(8);
		vert.pos.w = 1;

		vert.color.x = LuaManager::GetValue<float>(9);
		vert.color.y = LuaManager::GetValue<float>(10);
		vert.color.z = LuaManager::GetValue<float>(11);

		vert.texCoord.x = 1;
		vert.texCoord.y = 1;

		Line::Instance()->PushVertex(vert);

		return 0;
	}

	void Line::Draw()
	{
		if (lines_.size() > 0)
		{
			BLOW_SAFE_RELEASE_NB(vertexBuffer_);

			D3D11DisplayDevice* displayDevice = D3D11DisplayDevice::Instance();

			vertexBuffer_ = displayDevice->CreateVertexBuffer(lines_);

			displayDevice->SetVertexBuffer(vertexBuffer_);

			displayDevice->SetTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_LINELIST);

			displayDevice->SetShader(ContentManager::Instance()->GetShader(BASE_SHADER));
			displayDevice->SetShaderResources(ContentManager::Instance()->GetTexture(BASE_TEXTURE));

			displayDevice->UpdateConstantBuffer(XMMatrixIdentity(), displayDevice->GetCamera()->GetView(), displayDevice->GetCamera()->GetProjection(), 1);

			displayDevice->GetContext()->Draw(static_cast<UINT>(lines_.size()), 0);

			lines_.clear();
		}
	}

	Line::~Line()
	{
		BLOW_SAFE_RELEASE_NB(vertexBuffer_);
	};
}