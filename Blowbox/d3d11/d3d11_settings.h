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
		D3D11Settings();

		D3D11Settings(lua_State* L);

		~D3D11Settings();

		static D3D11Settings* Instance();

		void SetResolution(const float& width, const float& height);

		const Resolution& GetResolution();

		static void LuaRegisterFunctions(lua_State* L);

		static int LuaSetResolution(lua_State* L);

		static int LuaGetResolution(lua_State* L);

		CLASSNAME("RenderSettings");
	private:
		Resolution resolution_;
	};
}