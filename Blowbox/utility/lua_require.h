#pragma once

#include "../../blowbox/lua/lua_register.h"

namespace blowbox
{
	/**
	* @class blowbox::LuaRequire
	* @brief Requires a file from lua
	* @author Riko Ophorst
	*/
	class LuaRequire
	{
	public:
		/**
		* @brief Default LuaRequire constructor
		*/
		LuaRequire();

		/**
		* @brief Default LuaRequire constructor
		* @param[in] L (lua_State*) the lua state
		*/
		LuaRequire(lua_State* L);

		/**
		* @brief Default LuaRequire destructor
		*/
		~LuaRequire();

		/**
		* @brief Requires a file
		* @param[in] L (lua_State*) the lua state
		*/
		static int Require(lua_State* L);
	};
}