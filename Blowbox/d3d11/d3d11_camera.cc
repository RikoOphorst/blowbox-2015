#include "../../blowbox/d3d11/d3d11_camera.h"

#include "../../blowbox/d3d11/d3d11.h"
#include "../../blowbox/utility/lua_enum.h"
#include "../../blowbox/d3d11/d3d11_settings.h"

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
	D3D11Camera::D3D11Camera(lua_State* L) :
		position_(XMVectorSet(0.0f, 0.0f, -100.0f, 1.0f)),
		target_(XMVectorSet(0.0f, 0.0f, 1.0f, 1.0f)),
		up_(XMVectorSet(0.0f, 1.0f, 0.0f, 1.0f)),
		nearz_(0.001f),
		farz_(1000.0f),
		fov_(0.2f * 3.14f),
		mode_(CAMERA_PROJECTION_TYPE::CAMERA_PROJECTION_ORTHOGRAPHIC),
		LuaClass(L)
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
				D3D11Settings::Instance()->GetResolution().width, 
				D3D11Settings::Instance()->GetResolution().height,
				nearz_, 
				farz_	
			);
		}
		else if (CAMERA_PROJECTION_TYPE::CAMERA_PROJECTION_PERSPECTIVE == mode_)
		{
			projection_ = XMMatrixPerspectiveFovLH(fov_, D3D11Settings::Instance()->GetResolution().width / D3D11Settings::Instance()->GetResolution().height, nearz_, farz_);
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
	void D3D11Camera::SetFOV(const float& fov)
	{
		fov_ = fov;
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

	//------------------------------------------------------------------------------------------------------
	void D3D11Camera::LuaRegisterFunctions(lua_State* L)
	{
		luaL_Reg regist[] = {
			{ "setPosition", LuaSetPosition },
			{ "getPosition", LuaGetPosition },
			{ "setTarget", LuaSetTarget },
			{ "getTarget", LuaGetTarget },
			{ "setUp", LuaSetUp },
			{ "getUp", LuaGetUp },
			{ "setPosition2D", LuaSetPosition2D },
			{ "getPosition2D", LuaGetPosition2D },
			{ "setTarget2D", LuaSetTarget2D },
			{ "getTarget2D", LuaGetTarget2D },
			{ "setUp2D", LuaSetUp2D },
			{ "getUp2D", LuaGetUp2D },
			{ "setMode", LuaSetMode },
			{ "getMode", LuaGetMode },
			{ "setNearZ", LuaSetNearZ },
			{ "getNearZ", LuaGetNearZ },
			{ "setFarZ", LuaSetFarZ },
			{ "getFarZ", LuaGetFarZ },
			{ "setFOV", LuaSetFOV },
			{ "getFOV", LuaGetFOV },
			{ NULL, NULL }
		};

		LuaEnum::Set(L, "CameraModes", {
			"Orthographic",
			"Perspective"
		});

		luaL_register(L, NULL, regist);
	}

	//------------------------------------------------------------------------------------------------------
	int D3D11Camera::LuaSetPosition(lua_State* L)
	{
		D3D11Camera* self = LuaWrapper::Instance()->ParseUserdata<D3D11Camera>(L, 1);

		self->SetPosition(
			static_cast<float>(LuaWrapper::Instance()->Get<double>(L, 2)),
			static_cast<float>(LuaWrapper::Instance()->Get<double>(L, 3)),
			static_cast<float>(LuaWrapper::Instance()->Get<double>(L, 4)));

		return 0;
	}

	//------------------------------------------------------------------------------------------------------
	int D3D11Camera::LuaGetPosition(lua_State* L)
	{
		D3D11Camera* self = LuaWrapper::Instance()->ParseUserdata<D3D11Camera>(L, 1);

		XMFLOAT4 pos;
		XMStoreFloat4(&pos, self->GetPosition());

		return LuaWrapper::Instance()->Push(L, pos.x, pos.y, pos.z);
	}

	//------------------------------------------------------------------------------------------------------
	int D3D11Camera::LuaSetTarget(lua_State* L)
	{
		D3D11Camera* self = LuaWrapper::Instance()->ParseUserdata<D3D11Camera>(L, 1);

		self->SetTarget(
			static_cast<float>(LuaWrapper::Instance()->Get<double>(L, 2)),
			static_cast<float>(LuaWrapper::Instance()->Get<double>(L, 3)),
			static_cast<float>(LuaWrapper::Instance()->Get<double>(L, 4)));

		return 0;
	}

	//------------------------------------------------------------------------------------------------------
	int D3D11Camera::LuaGetTarget(lua_State* L)
	{
		D3D11Camera* self = LuaWrapper::Instance()->ParseUserdata<D3D11Camera>(L, 1);

		XMFLOAT4 pos;
		XMStoreFloat4(&pos, self->GetTarget());

		return LuaWrapper::Instance()->Push(L, pos.x, pos.y, pos.z);
	}

	//------------------------------------------------------------------------------------------------------
	int D3D11Camera::LuaSetUp(lua_State* L)
	{
		D3D11Camera* self = LuaWrapper::Instance()->ParseUserdata<D3D11Camera>(L, 1);

		self->SetUp(
			static_cast<float>(LuaWrapper::Instance()->Get<double>(L, 2)),
			static_cast<float>(LuaWrapper::Instance()->Get<double>(L, 3)),
			static_cast<float>(LuaWrapper::Instance()->Get<double>(L, 4)));

		return 0;
	}

	//------------------------------------------------------------------------------------------------------
	int D3D11Camera::LuaGetUp(lua_State* L)
	{
		D3D11Camera* self = LuaWrapper::Instance()->ParseUserdata<D3D11Camera>(L, 1);

		XMFLOAT4 pos;
		XMStoreFloat4(&pos, self->GetUp());

		return LuaWrapper::Instance()->Push(L, pos.x, pos.y, pos.z);
	}

	//------------------------------------------------------------------------------------------------------
	int D3D11Camera::LuaSetPosition2D(lua_State* L)
	{
		D3D11Camera* self = LuaWrapper::Instance()->ParseUserdata<D3D11Camera>(L, 1);

		self->SetPosition(
			static_cast<float>(LuaWrapper::Instance()->Get<double>(L, 2)),
			static_cast<float>(LuaWrapper::Instance()->Get<double>(L, 3)),
			-10.0f);

		return 0;
	}

	//------------------------------------------------------------------------------------------------------
	int D3D11Camera::LuaGetPosition2D(lua_State* L)
	{
		D3D11Camera* self = LuaWrapper::Instance()->ParseUserdata<D3D11Camera>(L, 1);

		XMFLOAT4 pos;
		XMStoreFloat4(&pos, self->GetPosition());

		return LuaWrapper::Instance()->Push(L, pos.x, pos.y, pos.z);
	}

	//------------------------------------------------------------------------------------------------------
	int D3D11Camera::LuaSetTarget2D(lua_State* L)
	{
		D3D11Camera* self = LuaWrapper::Instance()->ParseUserdata<D3D11Camera>(L, 1);

		self->SetTarget(
			static_cast<float>(LuaWrapper::Instance()->Get<double>(L, 2)),
			static_cast<float>(LuaWrapper::Instance()->Get<double>(L, 3)),
			0.0f);

		return 0;
	}

	//------------------------------------------------------------------------------------------------------
	int D3D11Camera::LuaGetTarget2D(lua_State* L)
	{
		D3D11Camera* self = LuaWrapper::Instance()->ParseUserdata<D3D11Camera>(L, 1);

		XMFLOAT4 pos;
		XMStoreFloat4(&pos, self->GetTarget());

		return LuaWrapper::Instance()->Push(L, pos.x, pos.y, pos.z);
	}

	//------------------------------------------------------------------------------------------------------
	int D3D11Camera::LuaSetUp2D(lua_State* L)
	{
		D3D11Camera* self = LuaWrapper::Instance()->ParseUserdata<D3D11Camera>(L, 1);

		self->SetUp(
			static_cast<float>(LuaWrapper::Instance()->Get<double>(L, 2)),
			static_cast<float>(LuaWrapper::Instance()->Get<double>(L, 3)),
			0.0f);

		return 0;
	}

	//------------------------------------------------------------------------------------------------------
	int D3D11Camera::LuaGetUp2D(lua_State* L)
	{
		D3D11Camera* self = LuaWrapper::Instance()->ParseUserdata<D3D11Camera>(L, 1);

		XMFLOAT4 pos;
		XMStoreFloat4(&pos, self->GetUp());

		return LuaWrapper::Instance()->Push(L, pos.x, pos.y, pos.z);
	}

	//------------------------------------------------------------------------------------------------------
	int D3D11Camera::LuaSetMode(lua_State* L)
	{
		D3D11Camera* self = LuaWrapper::Instance()->ParseUserdata<D3D11Camera>(L, 1);

		self->SetMode(static_cast<CAMERA_PROJECTION_TYPE>(static_cast<int>(LuaWrapper::Instance()->Get<double>(L, -1))));

		return 0;
	}

	//------------------------------------------------------------------------------------------------------
	int D3D11Camera::LuaGetMode(lua_State* L)
	{
		D3D11Camera* self = LuaWrapper::Instance()->ParseUserdata<D3D11Camera>(L, 1);

		return LuaWrapper::Instance()->Push(L, static_cast<int>(self->GetMode()));
	}

	//------------------------------------------------------------------------------------------------------
	int D3D11Camera::LuaSetNearZ(lua_State* L)
	{
		D3D11Camera* self = LuaWrapper::Instance()->ParseUserdata<D3D11Camera>(L, 1);

		self->SetNearZ(static_cast<float>(LuaWrapper::Instance()->Get<double>(L, 2)));

		return 0;
	}

	//------------------------------------------------------------------------------------------------------
	int D3D11Camera::LuaGetNearZ(lua_State* L)
	{
		D3D11Camera* self = LuaWrapper::Instance()->ParseUserdata<D3D11Camera>(L, 1);

		return LuaWrapper::Instance()->Push(L, self->GetNearZ());
	}

	//------------------------------------------------------------------------------------------------------
	int D3D11Camera::LuaSetFarZ(lua_State* L)
	{
		D3D11Camera* self = LuaWrapper::Instance()->ParseUserdata<D3D11Camera>(L, 1);

		self->SetFarZ(static_cast<float>(LuaWrapper::Instance()->Get<double>(L, 2)));

		return 0;
	}

	//------------------------------------------------------------------------------------------------------
	int D3D11Camera::LuaGetFarZ(lua_State* L)
	{
		D3D11Camera* self = LuaWrapper::Instance()->ParseUserdata<D3D11Camera>(L, 1);

		return LuaWrapper::Instance()->Push(L, self->GetFarZ());
	}

	//------------------------------------------------------------------------------------------------------
	int D3D11Camera::LuaSetFOV(lua_State* L)
	{
		D3D11Camera* self = LuaWrapper::Instance()->ParseUserdata<D3D11Camera>(L, 1);

		self->SetFOV(static_cast<float>(LuaWrapper::Instance()->Get<double>(L, 2)));

		return 0;
	}

	//------------------------------------------------------------------------------------------------------
	int D3D11Camera::LuaGetFOV(lua_State* L)
	{
		D3D11Camera* self = LuaWrapper::Instance()->ParseUserdata<D3D11Camera>(L, 1);

		return LuaWrapper::Instance()->Push(L, self->GetFOV());
	}
}