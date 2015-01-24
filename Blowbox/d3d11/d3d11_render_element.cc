#include "d3d11_render_element.h"

namespace blowbox
{
	D3D11RenderElement::D3D11RenderElement()
		: texture_(new D3D11Texture())
		, shader_(new D3D11Shader("shaders/effects.fx"))
	{
		SetPosition(0.0f, 0.0f, 0.0f);
		SetRotation(0.0f, 0.0f, 0.0f);
		SetScale(1.0f, 1.0f, 1.0f);
		SetAlpha(1.0f);

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
		delete texture_;
		delete shader_;
	}

	XMMATRIX& D3D11RenderElement::GetWorld()
	{
		float sx = XMVectorGetX(scale_) * size_.x;
		float sy = XMVectorGetY(scale_) * size_.y;
		world_ = XMMatrixScaling(sx, sy, XMVectorGetZ(scale_)) * XMMatrixRotationRollPitchYawFromVector(rotation_) * XMMatrixTranslationFromVector(position_);
		return world_;
	}

	void D3D11RenderElement::SetTexture(D3D11Texture* texture)
	{
		texture_ = texture;
	}

	D3D11Texture* D3D11RenderElement::GetTexture()
	{
		return texture_;
	}

	void D3D11RenderElement::SetShader(D3D11Shader* shader)
	{
		shader_ = shader;
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
}