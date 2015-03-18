#pragma once

#include "../../blowbox/d3d11/d3d11.h"

#include "../../blowbox/d3d11/d3d11_render_element.h"
#include "../../blowbox/lua/lua_class.h"

namespace blowbox
{
	/**
	* @class blowbox::Cube
	* @brief A Cube element with 8 vertices
	* @author Riko Ophorst
	*/
	class Cube : public D3D11RenderElement
	{
	public:
		/**
		* @brief Default Cube constructor
		*/
		Cube();

		/**
		* @brief Lua Cube constructor
		* @param[in] L (lua_State*) the lua state
		*/
		Cube(lua_State* L);

		/**
		* @brief Default Quad destructor
		*/
		~Cube();

		/**
		* @brief Creates the vertex buffer
		*/
		void Create();

		/**
		* @brief Registers all the lua functions
		* @param[in] L (lua_State*) the lua state
		*/
		static void LuaRegisterFunctions(lua_State* L);

		CLASSNAME("Cube");
	};
}