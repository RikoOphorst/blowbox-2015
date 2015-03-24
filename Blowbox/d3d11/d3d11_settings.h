#pragma once

#include "../../blowbox/d3d11/d3d11.h"
#include "../../blowbox/lua/lua_class.h"

namespace blowbox
{
	/**
	* @struct blowbox::Resolution
	* @brief Defines the resolution of the main window
	*/
	struct Resolution
	{
		float width, height;
	};
	
	/**
	* @class blowbox::D3D11Settings
	* @brief Keeps all the settings
	* @author Riko Ophorst
	*/
	class D3D11Settings: public LuaClass
	{
	public:
		/**
		* @brief Default D3D11Settings constructor
		*/
		D3D11Settings();

		/**
		* @brief Lua D3D11Settings constructor
		* @param[in] L (lua_State*) the lua state
		*/
		D3D11Settings(lua_State* L);

		/**
		* @brief Default D3D11Settings destructor
		*/
		~D3D11Settings();

		/**
		* @brief Gets an instance of the settings
		*/
		static D3D11Settings* Instance();

		/**
		* @brief Sets the resolution
		* @param[in] width (const float&) the width of the resolution
		* @param[in] height (const float&) the height of the resolution
		*/
		void SetResolution(const float& width, const float& height);

		/**
		* @brief Gets the resolution
		*/
		const Resolution& GetResolution();

		/**
		* @brief Sets the vsync
		* @param[in] vsync (const bool&) vsync
		*/
		void SetVSync(const bool& vsync);

		/**
		* @brief Gets the vsync
		*/
		const bool& GetVSync();

		/**
		* @brief Registers this object's functions
		* @param[in] L (lua_State*) the lua state
		*/
		static void LuaRegisterFunctions(lua_State* L);

		/**
		* @brief Sets the resolution via lua
		* @param[in] L (lua_State*) the lua state
		*/
		static int LuaSetResolution(lua_State* L);

		/**
		* @brief Gets the resolution via lua
		* @param[in] L (lua_State*) the lua state
		*/
		static int LuaGetResolution(lua_State* L);

		/**
		* @brief Sets the vsync via lua
		* @param[in] L (lua_State*) the lua state
		*/
		static int LuaSetVSync(lua_State* L);

		/**
		* @brief Gets the vsync via lua
		* @param[in] L (lua_State*) the lua state
		*/
		static int LuaGetVSync(lua_State* L);

		CLASSNAME("RenderSettings");
	private:
		Resolution resolution_;

		bool vsync_;
	};
}