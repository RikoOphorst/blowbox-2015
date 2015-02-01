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

	D3D11Camera::D3D11Camera(lua_State* state)
	{
		SetPosition(0.0f, 0.0f, -1.0f);
		SetUp(0.0f, 1.0f, 0.0f);
		SetNearZ(0.0f);
		SetFarZ(1000.0f);
		SetFOV(0.40f * 3.14f);

		mode_ = D3D11CameraMode::CAM_ORTHOGRAPHIC;
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

	float& D3D11Camera::GetNearZ()
	{
		return nearZ_;
	};

	float& D3D11Camera::GetFarZ()
	{
		return farZ_;
	};

	float& D3D11Camera::GetFOV()
	{
		return fov_;
	};

	D3D11CameraMode& D3D11Camera::GetMode()
	{
		return mode_;
	};

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

	int D3D11Camera::RegisterFunctions(lua_State* state)
	{
		luaL_Reg regist[] =
		{
			{ "getPosition", LuaGetPosition },
			{ "setPosition", LuaSetPosition },
			{ "getTarget", LuaGetTarget },
			{ "setTarget", LuaSetTarget },
			{ "getUp", LuaGetUp },
			{ "setUp", LuaSetUp },
			{ "getNearZ", LuaGetNearZ },
			{ "setNearZ", LuaSetNearZ },
			{ "getFarZ", LuaGetFarZ },
			{ "setFarZ", LuaSetFarZ },
			{ "getFOV", LuaGetFOV },
			{ "setFOV", LuaSetFOV },
			{ "getMode", LuaGetMode },
			{ "setMode", LuaSetMode },
			{ NULL, NULL }
		};

		LM_REGISTER(state, regist);

		return 0;
	}

	int D3D11Camera::LuaGetPosition(lua_State* state)
	{
		LuaManager::PushValue(XMVectorGetX(D3D11DisplayDevice::Instance()->GetCamera()->GetPosition()));
		LuaManager::PushValue(XMVectorGetY(D3D11DisplayDevice::Instance()->GetCamera()->GetPosition()));
		LuaManager::PushValue(XMVectorGetZ(D3D11DisplayDevice::Instance()->GetCamera()->GetPosition()));

		return 3;
	}

	int D3D11Camera::LuaSetPosition(lua_State* state)
	{
		float x = LuaManager::GetValue<float>(0);
		float y = LuaManager::GetValue<float>(1);
		float z = LuaManager::GetValue<float>(2);

		D3D11DisplayDevice::Instance()->GetCamera()->SetPosition(x, y, z);

		return 0;
	}

	int D3D11Camera::LuaGetTarget(lua_State* state)
	{
		LuaManager::PushValue(XMVectorGetX(D3D11DisplayDevice::Instance()->GetCamera()->GetTarget()));
		LuaManager::PushValue(XMVectorGetY(D3D11DisplayDevice::Instance()->GetCamera()->GetTarget()));
		LuaManager::PushValue(XMVectorGetZ(D3D11DisplayDevice::Instance()->GetCamera()->GetTarget()));

		return 3;
	}

	int D3D11Camera::LuaSetTarget(lua_State* state)
	{
		float x = LuaManager::GetValue<float>(0);
		float y = LuaManager::GetValue<float>(1);
		float z = LuaManager::GetValue<float>(2);

		D3D11DisplayDevice::Instance()->GetCamera()->SetTarget(x, y, z);

		return 0;
	}

	int D3D11Camera::LuaGetUp(lua_State* state)
	{
		LuaManager::PushValue(XMVectorGetX(D3D11DisplayDevice::Instance()->GetCamera()->GetUp()));
		LuaManager::PushValue(XMVectorGetY(D3D11DisplayDevice::Instance()->GetCamera()->GetUp()));
		LuaManager::PushValue(XMVectorGetZ(D3D11DisplayDevice::Instance()->GetCamera()->GetUp()));

		return 3;
	}

	int D3D11Camera::LuaSetUp(lua_State* state)
	{
		float x = LuaManager::GetValue<float>(0);
		float y = LuaManager::GetValue<float>(1);
		float z = LuaManager::GetValue<float>(2);

		D3D11DisplayDevice::Instance()->GetCamera()->SetUp(x, y, z);

		return 0;
	}

	int D3D11Camera::LuaGetNearZ(lua_State* state)
	{
		LuaManager::PushValue(D3D11DisplayDevice::Instance()->GetCamera()->GetNearZ());

		return 1;
	}

	int D3D11Camera::LuaSetNearZ(lua_State* state)
	{
		float x = LuaManager::GetValue<float>(0);

		D3D11DisplayDevice::Instance()->GetCamera()->SetNearZ(x);

		return 0;
	}

	int D3D11Camera::LuaGetFarZ(lua_State* state)
	{
		LuaManager::PushValue(D3D11DisplayDevice::Instance()->GetCamera()->GetFarZ());

		return 1;
	}

	int D3D11Camera::LuaSetFarZ(lua_State* state)
	{
		float x = LuaManager::GetValue<float>(0);

		D3D11DisplayDevice::Instance()->GetCamera()->SetFarZ(x);

		return 0;
	}

	int D3D11Camera::LuaGetFOV(lua_State* state)
	{
		LuaManager::PushValue(D3D11DisplayDevice::Instance()->GetCamera()->GetFOV());

		return 1;
	}

	int D3D11Camera::LuaSetFOV(lua_State* state)
	{
		float x = LuaManager::GetValue<float>(0);

		D3D11DisplayDevice::Instance()->GetCamera()->SetFOV(x);

		return 0;
	}

	int D3D11Camera::LuaGetMode(lua_State* state)
	{
		LuaManager::PushValue(D3D11DisplayDevice::Instance()->GetCamera()->GetMode());

		return 1;
	}

	int D3D11Camera::LuaSetMode(lua_State* state)
	{
		const char* x = LuaManager::GetValue<const char*>(0);
		D3D11CameraMode mode;

		if (strcmp(x, "orthographic") == 0) { mode = D3D11CameraMode::CAM_ORTHOGRAPHIC; }
		if (strcmp(x, "perspective") == 0) { mode = D3D11CameraMode::CAM_PERSPECTIVE; }

		D3D11DisplayDevice::Instance()->GetCamera()->SetMode(mode);

		return 0;
	}
}