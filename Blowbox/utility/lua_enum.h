#pragma once

#include "../../blowbox/lua/lua_class.h"
#include <vector>

namespace blowbox
{
	/**
	* @class LuaEnum
	* @brief Handles enumerators in lua
	* @author Riko Ophorst
	*/
	class LuaEnum : public LuaClass
	{
	public:
		/**
		* @brief Default LuaEnum constructor
		*/
		LuaEnum();

		/**
		* @brief Lua constructor for LuaEnum
		* @param[in] L (lua_State*) the lua state
		*/
		LuaEnum(lua_State* L);

		/**
		* @brief Default LuaEnum destructor
		*/
		~LuaEnum();

		/**
		* @brief Sets a global enumerator table in to the lua state
		* @param[in] L (lua_State*) the lua state
		* @param[in] identifier (const std::string&) the identifier this enumerator should have in the global table
		* @param[in] types (const std::vector<std::string>& the types the enumerator should have
		*/
		static void Set(lua_State* L, const std::string& identifier, const std::vector<std::string>& types);

		/**
		* @brief Resets the lua enumerator to something else
		* @param[in] L (lua_State*) the lua state
		*/
		static int LuaReset(lua_State* L);

		/**
		* @brief Registers this class' functions via luaL_register
		* @param[in] L (lua_State*) the lua state
		*/
		static void LuaRegisterFunctions(lua_State* L);

		CLASSNAME("enum");
	};
}