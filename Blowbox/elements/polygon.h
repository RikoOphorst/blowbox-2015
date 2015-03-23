#pragma once

#include <vector>

#include "../../blowbox/d3d11/d3d11_render_element.h"
#include "../../blowbox/d3d11/d3d11_vertex_buffer.h"

namespace blowbox
{
	/**
	* @class blowbox::Polygon
	* @brief Creates a polygon render element with varying shapes and sizes
	*/
	class Polygon: public D3D11RenderElement
	{
	public:
		/**
		* @brief Default Polygon constructor
		*/
		Polygon();

		/**
		* @brief Lua Polygon constructor
		* @param[in] L (lua_State*) the lua state
		*/
		Polygon(lua_State* L);

		/**
		* @brief Default Polygon destructor
		*/
		~Polygon();

		/**
		* @brief Creates the polygon vertex buffer
		*/
		void Create();

		/**
		* @brief Registers this object's functions
		* @param[in] L (lua_State*) the lua state
		*/
		static void LuaRegisterFunctions(lua_State* L);

		/**
		* @brief Sets this object's points via lua
		* @param[in] L (lua_State*) the lua state
		*/
		static int LuaSetPoints(lua_State* L);

		/**
		* @brief Gets this object's points via lua
		* @param[in] L (lua_State*) the lua state
		*/
		static int LuaGetPoints(lua_State* L);

		CLASSNAME("Polygon");
	private:
		std::vector<Vertex> vertices_;
	};
}