#include "d3d11_camera.h"

namespace blowbox
{
	D3D11Camera::D3D11Camera(D3D11CameraMode mode)
	{
		SetPosition(0.0f, 0.0f, -1.0f);
		SetUp(0.0f, 1.0f, 0.0f);
		SetNearZ(0.0f);
		SetFarZ(1000.0f);
		SetFOV(0.40f * 3.14f);

		mode_ = mode;
	}

	XMMATRIX& D3D11Camera::GetView()
	{
		view_ = XMMatrixLookAtLH(position_, target_, up_);
		return view_;
	};

	XMMATRIX& D3D11Camera::GetProjection()
	{
		if (mode_ == CAM_ORTHOGRAPHIC)
		{
			projection_ = XMMatrixOrthographicLH((float)D3D11DisplayDevice::Instance()->GetWidth(), (float)D3D11DisplayDevice::Instance()->GetHeight(), nearZ_, farZ_);
		}
		else
		{
			projection_ = XMMatrixPerspectiveFovLH(0.2f * 3.14f, (float)D3D11DisplayDevice::Instance()->GetWidth() / D3D11DisplayDevice::Instance()->GetHeight(), nearZ_, farZ_);
		}
		return projection_;
	};

	XMVECTOR& D3D11Camera::GetPosition()
	{
		return position_;
	};

	XMVECTOR& D3D11Camera::GetTarget()
	{
		return target_;
	};

	XMVECTOR& D3D11Camera::GetUp()
	{
		return up_;
	};

	D3D11CameraMode& D3D11Camera::GetMode()
	{
		return mode_;
	}

	void D3D11Camera::SetPosition(float x, float y, float z)
	{
		SetTarget(x, y, z + 1.0f);
		position_ = XMVectorSet(x, y, z, 0.0f);
	};

	void D3D11Camera::SetTarget(float x, float y, float z)
	{
		target_ = XMVectorSet(x, y, z, 0.0f);
	};

	void D3D11Camera::SetUp(float x, float y, float z)
	{
		up_ = XMVectorSet(x, y, z, 0.0f);
	};

	void D3D11Camera::SetNearZ(float z)
	{
		nearZ_ = z;
	}

	void D3D11Camera::SetFarZ(float z)
	{
		farZ_ = z;
	}

	void D3D11Camera::SetFOV(float fov)
	{
		fov_ = fov;
	}

	void D3D11Camera::SetMode(D3D11CameraMode mode)
	{
		mode_ = mode;
	}

	D3D11Camera::~D3D11Camera()
	{

	}
}