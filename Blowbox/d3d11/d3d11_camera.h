#pragma once

#include "d3d11_display_device.h"
#include "../lua/lua_manager.h"
#include "../lua/lua_class.h"

namespace blowbox
{
	enum D3D11CameraMode
	{
		CAM_ORTHOGRAPHIC,
		CAM_PERSPECTIVE
	};
	
	class D3D11Camera : public LuaClass
	{
	public:
		D3D11Camera(D3D11CameraMode mode);
		D3D11Camera(lua_State* state);
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

		static int RegisterFunctions(lua_State* state);

		static int LuaSetPosition(lua_State* state);
		static int LuaSetTarget(lua_State* state);
		static int LuaSetUp(lua_State* state);
		static int LuaSetNearZ(lua_State* state);
		static int LuaSetFarZ(lua_State* state);
		static int LuaSetFOV(lua_State* state);
		static int LuaSetMode(lua_State* state);

		static int LuaGetPosition(lua_State* state);
		static int LuaGetTarget(lua_State* state);
		static int LuaGetUp(lua_State* state);
		static int LuaGetNearZ(lua_State* state);
		static int LuaGetFarZ(lua_State* state);
		static int LuaGetFOV(lua_State* state);
		static int LuaGetMode(lua_State* state);

		LM_NAME("Camera");
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