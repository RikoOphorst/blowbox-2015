#include "d3d11_render_element.h"

#include "../geom/quad.h"

namespace blowbox
{
	D3D11RenderElement::D3D11RenderElement()
	{
		SetPosition(0.0f, 0.0f, 0.0f);
		SetRotation(0.0f, 0.0f, 0.0f);
		SetScale(1.0f, 1.0f, 1.0f);
		SetAlpha(1.0f);

		texture_ = ContentManager::Instance()->GetTexture("tex1.png");

		shader_ = ContentManager::Instance()->GetShader("shaders/effects.fx");

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

		float x = LuaManager::GetValue<float>(1);
		float y = LuaManager::GetValue<float>(2);
		float z = LuaManager::GetValue<float>(3);

		self->position_ = XMVectorSet(x, y, z, 1.0f);

		return 0;
	}
}