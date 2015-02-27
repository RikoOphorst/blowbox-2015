#include "../../blowbox/d3d11/d3d11_camera.h"

#include "../../blowbox/d3d11/d3d11.h"

namespace blowbox
{
	//------------------------------------------------------------------------------------------------------
	D3D11Camera::D3D11Camera() :
		position_(XMVectorSet(0.0f, 0.0f, -100.0f, 1.0f)),
		target_(XMVectorSet(0.0f, 0.0f, 1.0f, 1.0f)),
		up_(XMVectorSet(0.0f, 1.0f, 0.0f, 1.0f)),
		nearz_(0.001f),
		farz_(1000.0f),
		fov_(0.2f * 3.14f),
		mode_(CAMERA_PROJECTION_TYPE::CAMERA_PROJECTION_ORTHOGRAPHIC)
	{
		
	}

	//------------------------------------------------------------------------------------------------------
	D3D11Camera::~D3D11Camera()
	{

	}

	//------------------------------------------------------------------------------------------------------
	const XMVECTOR& D3D11Camera::GetPosition() const
	{
		return position_;
	}

	//------------------------------------------------------------------------------------------------------
	const float D3D11Camera::GetX() const
	{
		return XMVectorGetX(position_);
	}

	//------------------------------------------------------------------------------------------------------
	const float D3D11Camera::GetY() const
	{
		return XMVectorGetY(position_);
	}

	//------------------------------------------------------------------------------------------------------
	const float D3D11Camera::GetZ() const
	{
		return XMVectorGetZ(position_);
	}

	//------------------------------------------------------------------------------------------------------
	const float& D3D11Camera::GetNearZ() const
	{
		return nearz_;
	}

	//------------------------------------------------------------------------------------------------------
	const float& D3D11Camera::GetFarZ() const
	{
		return farz_;
	}

	//------------------------------------------------------------------------------------------------------
	const float& D3D11Camera::GetFOV() const
	{
		return fov_;
	}

	//------------------------------------------------------------------------------------------------------
	const CAMERA_PROJECTION_TYPE& D3D11Camera::GetMode() const
	{
		return mode_;
	}

	//------------------------------------------------------------------------------------------------------
	const XMVECTOR& D3D11Camera::GetTarget() const
	{
		return target_;
	}

	//------------------------------------------------------------------------------------------------------
	const XMVECTOR& D3D11Camera::GetUp() const
	{
		return up_;
	}

	//------------------------------------------------------------------------------------------------------
	const XMMATRIX& D3D11Camera::GetView()
	{
		view_ = XMMatrixLookAtLH(position_, target_, up_);

		return view_;
	}

	//------------------------------------------------------------------------------------------------------
	const XMMATRIX& D3D11Camera::GetProjection()
	{
		if (CAMERA_PROJECTION_TYPE::CAMERA_PROJECTION_ORTHOGRAPHIC == mode_)
		{
			projection_ = XMMatrixOrthographicLH(
				640, 
				480, 
				nearz_, 
				farz_	
			);
		}
		else if (CAMERA_PROJECTION_TYPE::CAMERA_PROJECTION_PERSPECTIVE == mode_)
		{
			projection_ = XMMatrixPerspectiveFovLH(fov_, (float)640 / 480, nearz_, farz_);
		}

		return projection_;
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11Camera::SetPosition(const float& x, const float& y, const float& z)
	{
		position_ = XMVectorSet(x, y, z, 1.0f);
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11Camera::SetX(const float& x)
	{
		position_ = XMVectorSetX(position_, x);
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11Camera::SetY(const float& y)
	{
		position_ = XMVectorSetY(position_, y);
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11Camera::SetZ(const float& z)
	{
		position_ = XMVectorSetZ(position_, z);
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11Camera::SetNearZ(const float& z)
	{
		nearz_ = z;
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11Camera::SetFarZ(const float& z)
	{
		farz_ = z;
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11Camera::SetMode(const CAMERA_PROJECTION_TYPE& mode)
	{
		mode_ = mode;
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11Camera::SetTarget(const float& x, const float& y, const float& z)
	{
		target_ = XMVectorSet(x, y, z, 1.0f);
	}

	//------------------------------------------------------------------------------------------------------
	void D3D11Camera::SetUp(const float& x, const float& y, const float& z)
	{
		up_ = XMVectorSet(x, y, z, 1.0f);
	}
}