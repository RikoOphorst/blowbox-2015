#pragma once

#include <Windows.h>
#include <xnamath.h>

#include "../../blowbox/logging.h"
#include "../../blowbox/lua/lua_class.h"

namespace blowbox
{
	/**
	* @enum blowbox::CAMERA_PROJECTION_TYPE
	* @brief All available projection types
	*/
	enum CAMERA_PROJECTION_TYPE
	{
		CAMERA_PROJECTION_ORTHOGRAPHIC,
		CAMERA_PROJECTION_PERSPECTIVE
	};

	/**
	* @class blowbox::D3D11Camera
	* @brief Handles a D3D11 camera and its matrix
	* @author Riko Ophorst
	*/
	class D3D11Camera: public LuaClass
	{
	public:
		/**
		* @brief Default D3D11Camera constructor
		*/
		D3D11Camera();

		/**
		* @brief Lua D3D11Camera constructor
		*/
		D3D11Camera(lua_State* L);

		/**
		* @brief Default D3D11Camera destructor
		*/
		~D3D11Camera();

		/**
		* @brief The position of the camera
		*/
		const XMVECTOR& GetPosition() const;

		/**
		* @brief The x-coordinate of the camera
		*/
		const float GetX() const;

		/**
		* @brief The y-coordinate of the camera
		*/
		const float GetY() const;

		/**
		* @brief The z-coordinate of the camera
		*/
		const float GetZ() const;

		/**
		* @brief The z value of the near z plane
		*/
		const float& GetNearZ() const;

		/**
		* @brief The z value of the far z plane
		*/
		const float& GetFarZ() const;

		/**
		* @brief The field of view of the camera
		*/
		const float& GetFOV() const;

		/**
		* @brief The projection mode / type of the camera
		*/
		const CAMERA_PROJECTION_TYPE& GetMode() const;

		/**
		* @brief The target vector of the camera
		*/
		const XMVECTOR& GetTarget() const;

		/**
		* @brief The up vector of the camera
		*/
		const XMVECTOR& GetUp() const;

		/**
		* @brief The view matrix of the camera
		*/
		const XMMATRIX& GetView();

		/**
		* @brief The projection matrix of the camera
		*/
		const XMMATRIX& GetProjection();

		/**
		* @brief Sets the position of the camera
		* @param[in] x (float) The x position
		* @param[in] y (float) The y position
		* @param[in] z (float) The z position
		*/
		void SetPosition(const float& x, const float& y, const float& z);

		/**
		* @brief Sets the x position of the camera
		* @param[in] x (float) The x position
		*/
		void SetX(const float& x);

		/**
		* @brief Sets the x position of the camera
		* @param[in] y (float) The y position
		*/
		void SetY(const float& y);

		/**
		* @brief Sets the x position of the camera
		* @param[in] z (float) The z position
		*/
		void SetZ(const float& z);

		/**
		* @brief Sets the near z plane of the camera
		* @param[in] z (const float&) the z value
		*/
		void SetNearZ(const float& z);

		/**
		* @brief Sets the far z plane of the camera
		* @param[in] z (const float&) the z value
		*/
		void SetFarZ(const float& z);

		/**
		* @brief Sets the FOV
		* @param[in] fov (const float&) the fov to be set
		*/
		void SetFOV(const float& fov);

		/**
		* @brief Sets the mode
		* @param[in] mode (const CAMERA_PROJECTION_TYPE&) the mode to be set
		*/
		void SetMode(const CAMERA_PROJECTION_TYPE& mode);

		/**
		* @brief Sets the target
		* @param[in] x (const float&) the x coordinate of the target to be set
		* @param[in] y (const float&) the y coordinate of the target to be set
		* @param[in] z (const float&) the z coordinate of the target to be set
		*/
		void SetTarget(const float& x, const float& y, const float& z);

		/**
		* @brief Sets the up
		* @param[in] x (const float&) the x coordinate of the up to be set
		* @param[in] y (const float&) the y coordinate of the up to be set
		* @param[in] z (const float&) the z coordinate of the up to be set
		*/
		void SetUp(const float& x, const float& y, const float& z);

		/**
		* @brief Sets the position of the camera via lua
		* @param[in] L (lua_State*) the lua state
		*/
		static int LuaSetPosition(lua_State* L);

		/**
		* @brief Gets the position of the camera via lua
		* @param[in] L (lua_State*) the lua state
		*/
		static int LuaGetPosition(lua_State* L);

		/**
		* @brief Sets the target of the camera via lua
		* @param[in] L (lua_State*) the lua state
		*/
		static int LuaSetTarget(lua_State* L);

		/**
		* @brief Gets the target of the camera via lua
		* @param[in] L (lua_State*) the lua state
		*/
		static int LuaGetTarget(lua_State* L);

		/**
		* @brief Sets the up of the camera via lua
		* @param[in] L (lua_State*) the lua state
		*/
		static int LuaSetUp(lua_State* L);

		/**
		* @brief Gets the up of the camera via lua
		* @param[in] L (lua_State*) the lua state
		*/
		static int LuaGetUp(lua_State* L);

		/**
		* @brief Sets the position of the camera via lua
		* @param[in] L (lua_State*) the lua state
		*/
		static int LuaSetPosition2D(lua_State* L);

		/**
		* @brief Gets the position of the camera via lua
		* @param[in] L (lua_State*) the lua state
		*/
		static int LuaGetPosition2D(lua_State* L);

		/**
		* @brief Sets the target of the camera via lua
		* @param[in] L (lua_State*) the lua state
		*/
		static int LuaSetTarget2D(lua_State* L);

		/**
		* @brief Gets the target of the camera via lua
		* @param[in] L (lua_State*) the lua state
		*/
		static int LuaGetTarget2D(lua_State* L);

		/**
		* @brief Sets the up of the camera via lua
		* @param[in] L (lua_State*) the lua state
		*/
		static int LuaSetUp2D(lua_State* L);

		/**
		* @brief Gets the up of the camera via lua
		* @param[in] L (lua_State*) the lua state
		*/
		static int LuaGetUp2D(lua_State* L);

		/**
		* @brief Sets the near z of the camera via lua
		* @param[in] L (lua_State*) the lua state
		*/
		static int LuaSetNearZ(lua_State* L);

		/**
		* @brief Gets the near z of the camera via lua
		* @param[in] L (lua_State*) the lua state
		*/
		static int LuaGetNearZ(lua_State* L);

		/**
		* @brief Sets the far z of the camera via lua
		* @param[in] L (lua_State*) the lua state
		*/
		static int LuaSetFarZ(lua_State* L);

		/**
		* @brief Gets the far z of the camera via lua
		* @param[in] L (lua_State*) the lua state
		*/
		static int LuaGetFarZ(lua_State* L);

		/**
		* @brief Sets the fov of the camera via lua
		* @param[in] L (lua_State*) the lua state
		*/
		static int LuaSetFOV(lua_State* L);

		/**
		* @brief Gets the fov of the camera via lua
		* @param[in] L (lua_State*) the lua state
		*/
		static int LuaGetFOV(lua_State* L);

		/**
		* @brief Sets the mode of the camera via lua
		* @param[in] L (lua_State*) the lua state
		*/
		static int LuaSetMode(lua_State* L);

		/**
		* @brief Gets the mode of the camera via lua
		* @param[in] L (lua_State*) the lua state
		*/
		static int LuaGetMode(lua_State* L);

		CLASSNAME("Camera");
	private:
		XMVECTOR position_;
		XMVECTOR target_;
		XMVECTOR up_;
		float nearz_;
		float farz_;
		float fov_;
		XMMATRIX projection_;
		XMMATRIX view_;
		CAMERA_PROJECTION_TYPE mode_;
	};
}