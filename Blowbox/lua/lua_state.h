#pragma once

#include "../../blowbox/memory/shared_ptr.h"
#include "../../blowbox/lua/lua.h"

namespace blowbox
{
	/**
	* @class blowbox::LuaState
	* @brief Manages the lua state
	*/
	class LuaState
	{
	public:
		/**
		* @brief Default LuaState constructor
		*/
		LuaState();

		/**
		* @brief Default LuaState destructor
		*/
		~LuaState();

		/**
		* @brief Retrieves the LuaState instance
		*/
		static LuaState* Instance();

		/**
		* @brief Opens the default libraries
		*/
		void OpenLibs();

		/**
		* @brief Retrieves the lua_State* object
		*/
		lua_State* Get();
	private:
		lua_State* L_;
	};
}