#include "../../blowbox/d3d11/d3d11_render_element.h"

#include "../../blowbox/d3d11/d3d11_texture.h"

namespace blowbox
{
	//------------------------------------------------------------------------------------------------------
	D3D11RenderElement::D3D11RenderElement()
	{

	}

	//------------------------------------------------------------------------------------------------------
	D3D11RenderElement::~D3D11RenderElement()
	{

	}

	//------------------------------------------------------------------------------------------------------
	const XMVECTOR& D3D11RenderElement::GetPosition() const
	{
		return v_position_;
	}

	//------------------------------------------------------------------------------------------------------
	const float& D3D11RenderElement::GetX() const
	{
		return position_.x;
	}

	//------------------------------------------------------------------------------------------------------
	const float& D3D11RenderElement::GetY() const
	{
		return position_.y;
	}

	//------------------------------------------------------------------------------------------------------
	const float& D3D11RenderElement::GetZ() const
	{
		return position_.z;
	}

	//------------------------------------------------------------------------------------------------------
	const XMVECTOR& D3D11RenderElement::GetRotation() const
	{
		return v_rotation_;
	}

	//------------------------------------------------------------------------------------------------------
	const XMVECTOR& D3D11RenderElement::GetScale() const
	{
		return v_scaling_;
	}

	//------------------------------------------------------------------------------------------------------
	const XMVECTOR& D3D11RenderElement::GetOffset() const
	{
		return v_offset_;
	}

	//------------------------------------------------------------------------------------------------------
	const double& D3D11RenderElement::GetAlpha() const
	{
		return alpha_;
	}

	//------------------------------------------------------------------------------------------------------
	D3D11Texture* D3D11RenderElement::GetTexture() const
	{
		return texture_;
	}

	//------------------------------------------------------------------------------------------------------
	D3D11Shader* D3D11RenderElement::GetShader() const
	{
		return shader_;
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11RenderElement::SetPosition(float x, float y, float z)
	{
		position_.x = x;
		position_.y = y;
		position_.z = z;

		CalculatePosition();
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11RenderElement::SetX(float x)
	{
		position_.x = x;
		CalculatePosition();
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11RenderElement::SetY(float y)
	{
		position_.y = y;
		CalculatePosition();
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11RenderElement::SetZ(float z)
	{
		position_.z = z;
		CalculatePosition();
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11RenderElement::SetRotation(float x, float y, float z)
	{
		rotation_.x = x;
		rotation_.y = y;
		rotation_.z = z;
		CalculateRotation();
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11RenderElement::SetScale(float x, float y, float z)
	{
		scaling_.x = x;
		scaling_.y = y;
		scaling_.z = z;
		CalculateScaling();
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11RenderElement::SetOffset(float x, float y, float z)
	{
		offset_.x = x;
		offset_.y = y;
		offset_.z = z;
		CalculateOffset();
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11RenderElement::SetTexture(std::string path)
	{
		/**
		* @todo Implement the content manager
		*/
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11RenderElement::SetShader(std::string path)
	{
		/**
		* @todo Implement the content manager
		*/
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11RenderElement::CalculatePosition()
	{
		v_position_ = XMVectorSet(position_.x, position_.y, position_.z, 1.0f);
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11RenderElement::CalculateRotation()
	{
		v_rotation_ = XMVectorSet(rotation_.x, rotation_.y, rotation_.z, 1.0f);
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11RenderElement::CalculateScaling()
	{
		v_scaling_ = XMVectorSet(scaling_.x, scaling_.y, scaling_.z, 1.0f);
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11RenderElement::CalculateOffset()
	{
		v_offset_ = XMVectorSet(offset_.x, offset_.y, offset_.z, 1.0f);
	}
}