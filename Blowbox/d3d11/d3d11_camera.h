#pragma once

#include "d3d11_display_device.h"

namespace blowbox
{
	enum D3D11CameraMode
	{
		CAM_ORTHOGRAPHIC,
		CAM_PERSPECTIVE
	};
	
	class D3D11Camera
	{
	public:
		D3D11Camera(D3D11CameraMode mode);
		~D3D11Camera();

		XMMATRIX&				GetView();
		XMMATRIX&				GetProjection();

		XMVECTOR&				GetPosition();
		XMVECTOR&				GetTarget();
		XMVECTOR&				GetUp();
		float&					GetNearZ();
		float&					GetFarZ();
		float&					GetFOV();
		D3D11CameraMode&		GetMode();

		void					SetPosition(float x, float y, float z);
		void					SetTarget(float x, float y, float z);
		void					SetUp(float x, float y, float z);
		void					SetNearZ(float z);
		void					SetFarZ(float z);
		void					SetFOV(float fov);
		void					SetMode(D3D11CameraMode mode);
	private:
		XMMATRIX				view_;
		XMMATRIX				projection_;
		XMVECTOR				position_;
		XMVECTOR				target_;
		XMVECTOR				up_;
		D3D11CameraMode			mode_;
		float					nearZ_;
		float					farZ_;
		float					fov_;
	};
}