#pragma once

#include "../../blowbox/d3d11/d3d11.h"

#include "../../blowbox/d3d11/d3d11_render_element.h"
#include "../../blowbox/lua/lua_class.h"

namespace blowbox
{
	/**
	* @class blowbox::Quad
	* @brief A Quad element with 4 vertices
	* @author Riko Ophorst
	*/
	class Quad : public D3D11RenderElement
	{
	public:
		/**
		* @brief Default Quad constructor
		*/
		Quad();
		
		/**
		* @brief Lua Quad constructor
		* @param[in] L (lua_State*) the lua state
		*/
		Quad(lua_State* L);

		/**
		* @brief Default Quad destructor
		*/
		~Quad();

		/**
		* @brief Creates the vertex buffer
		*/
		void Create();

		/**
		* @brief Registers all the lua functions
		* @param[in] L (lua_State*) the lua state
		*/
		static void LuaRegisterFunctions(lua_State* L);

		CLASSNAME("Quad");
	};
}