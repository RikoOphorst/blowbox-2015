#include "d3d11_render_element.h"

#include "../geom/quad.h"
#include "../content/content_manager.h"
#include "../d3d11/d3d11_shader.h"
#include "../d3d11/d3d11_texture.h"
#include "../d3d11/d3d11_camera.h"

namespace blowbox
{
	D3D11RenderElement::D3D11RenderElement()
	{
		SetPosition(0.0f, 0.0f, 0.0f);
		SetRotation(0.0f, 0.0f, 0.0f);
		SetScale(1.0f, 1.0f, 1.0f);
		SetAlpha(1.0f);

		texture_ = ContentManager::Instance()->GetTexture(BASE_TEXTURE);
		shader_ = ContentManager::Instance()->GetShader(BASE_SHADER);

		if (D3D11DisplayDevice::Instance()->GetCamera()->GetMode() == CAM_ORTHOGRAPHIC)
		{
			SetSize(50.0f, 50.0f);
		}
		else
		{
			SetSize(1.0f, 1.0f);
		}
	}

	D3D11RenderElement::~D3D11RenderElement()
	{
		
	}

	XMMATRIX& D3D11RenderElement::GetWorld()
	{
		float sx = XMVectorGetX(scale_) * size_.x;
		float sy = XMVectorGetY(scale_) * size_.y;
		world_ = XMMatrixScaling(sx, sy, XMVectorGetZ(scale_)) * XMMatrixRotationRollPitchYawFromVector(rotation_) * XMMatrixTranslationFromVector(position_);
		return world_;
	}

	void D3D11RenderElement::SetTopology(D3D11_PRIMITIVE_TOPOLOGY topology)
	{
		if (topology != topology_)
		{
			topology_ = topology;
		}
	}

	D3D11_PRIMITIVE_TOPOLOGY D3D11RenderElement::GetTopology()
	{
		return topology_;
	}

	void D3D11RenderElement::SetTexture(std::string path)
	{
		texture_ = ContentManager::Instance()->GetTexture(path);
	}

	D3D11Texture* D3D11RenderElement::GetTexture()
	{
		return texture_;
	}

	void D3D11RenderElement::SetShader(std::string path)
	{
		shader_ = ContentManager::Instance()->GetShader(path);
	}

	D3D11Shader* D3D11RenderElement::GetShader()
	{
		return shader_;
	}

	void D3D11RenderElement::SetPosition(float x, float y, float z)
	{
		position_ = XMVectorSet(x, y, z, 1.0f);
	}

	XMVECTOR& D3D11RenderElement::GetPosition()
	{
		return position_;
	}

	void D3D11RenderElement::SetRotation(float x, float y, float z)
	{
		rotation_ = XMVectorSet(x, y, z, 1.0f);
	}

	XMVECTOR& D3D11RenderElement::GetRotation()
	{
		return rotation_;
	}

	void D3D11RenderElement::SetScale(float x, float y, float z)
	{
		scale_ = XMVectorSet(x, y, z, 1.0f);
	}

	XMVECTOR& D3D11RenderElement::GetScale()
	{
		return scale_;
	}

	void D3D11RenderElement::SetAlpha(float a)
	{
		alpha_ = a;
	}

	float& D3D11RenderElement::GetAlpha()
	{
		return alpha_;
	}

	void D3D11RenderElement::SetSize(float w, float h)
	{
		size_.x = w;
		size_.y = h;
	}

	XMFLOAT2& D3D11RenderElement::GetSize()
	{
		return size_;
	}

	int D3D11RenderElement::LuaGetAlpha(lua_State* state)
	{
		LM_GETSELF(D3D11RenderElement);
		LuaManager::PushValue(self->alpha_);
		return 1;
	}

	int D3D11RenderElement::LuaSetAlpha(lua_State* state)
	{
		LM_GETSELF(D3D11RenderElement);
		self->SetAlpha(LuaManager::GetValue<float>(1));
		return 0;
	}

	int D3D11RenderElement::LuaGetPosition(lua_State* state)
	{
		LM_GETSELF(D3D11RenderElement);
		LuaManager::PushValue(XMVectorGetX(self->position_));
		LuaManager::PushValue(XMVectorGetY(self->position_));
		LuaManager::PushValue(XMVectorGetZ(self->position_));
		return 3;
	}

	int D3D11RenderElement::LuaSetPosition(lua_State* state)
	{
		LM_GETSELF(D3D11RenderElement);
		self->SetPosition(
			LuaManager::GetValue<float>(1), 
			LuaManager::GetValue<float>(2), 
			LuaManager::GetValue<float>(3)
		);
		return 0;
	}

	int D3D11RenderElement::LuaGetShader(lua_State* state)
	{
		LM_GETSELF(D3D11RenderElement);
		LuaManager::PushValue(self->shader_->GetPath());
		return 1;
	}

	int D3D11RenderElement::LuaSetShader(lua_State* state)
	{
		LM_GETSELF(D3D11RenderElement);
		self->shader_->Set(LuaManager::GetValue<std::string>(1));
		return 0;
	}

	int D3D11RenderElement::LuaGetTexture(lua_State* state)
	{
		LM_GETSELF(D3D11RenderElement);
		LuaManager::PushValue(self->texture_->GetPath());
		return 1;
	}

	int D3D11RenderElement::LuaSetTexture(lua_State* state)
	{
		LM_GETSELF(D3D11RenderElement);
		self->texture_->Set(LuaManager::GetValue<std::string>(1));
		return 0;
	}

	int D3D11RenderElement::LuaGetRotation(lua_State* state)
	{
		LM_GETSELF(D3D11RenderElement);
		LuaManager::PushValue(XMVectorGetX(self->GetRotation()));
		LuaManager::PushValue(XMVectorGetY(self->GetRotation()));
		LuaManager::PushValue(XMVectorGetZ(self->GetRotation()));
		return 3;
	}

	int D3D11RenderElement::LuaSetRotation(lua_State* state)
	{
		LM_GETSELF(D3D11RenderElement);
		self->SetRotation(
			LuaManager::GetValue<float>(1),
			LuaManager::GetValue<float>(2),
			LuaManager::GetValue<float>(3)
		);
		return 0;
	}

	int D3D11RenderElement::LuaGetScale(lua_State* state)
	{
		LM_GETSELF(D3D11RenderElement);
		LuaManager::PushValue(XMVectorGetX(self->scale_));
		LuaManager::PushValue(XMVectorGetY(self->scale_));
		LuaManager::PushValue(XMVectorGetZ(self->scale_));
		return 3;
	}

	int D3D11RenderElement::LuaSetScale(lua_State* state)
	{
		LM_GETSELF(D3D11RenderElement);
		self->SetScale(
			LuaManager::GetValue<float>(1),
			LuaManager::GetValue<float>(2),
			LuaManager::GetValue<float>(3)
		);
		return 3;
	}
}