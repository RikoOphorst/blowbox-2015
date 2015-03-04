#pragma once

#include "../../blowbox/memory/shared_ptr.h"
#include "../../blowbox/lua/lua_state.h"

namespace blowbox
{
	/**
	* @class blowbox::LuaWrapper
	* @brief Wraps the Lua interface because it's ugly as shit
	* @author Riko Ophorst
	*/
	class LuaWrapper
	{
	public:
		/**
		* @brief Default LuaWrapper constructor
		*/
		LuaWrapper();
		
		/**
		* @brief Default LuaWrapper destructor
		*/
		~LuaWrapper();

		/**
		* @brief Retrieves the lua wrapper instance
		*/
		static LuaWrapper* Instance();

		/**
		* @brief Parses userdata to given object type
		* @param[in] L (lua_State*) the lua state
		* @param[in] index (const int&) the index on the lua stack that should be parsed
		*/
		template<typename T>
		T* ParseUserdata(lua_State* L, const int& index);

		/**
		* @brief Dumps the stack in the subsystem's console window
		* @param[in] L (lua_State*) the lua state
		* @param[in] brief (lua_State*) brief description of what the dump should be headed by
		* @todo make it dump in the actual subsystem
		*/
		void Dump(lua_State* L, const std::string& brief);
	};

	//------------------------------------------------------------------------------------------------------
	template<typename T>
	T* LuaWrapper::ParseUserdata(lua_State* L, const int& index)
	{
		if (!lua_isuserdata(L, index))
		{
			BLOW_BREAK("Error while parsing user data to an object, maybe you used a dot/period instead of a colon to access the object?");
		}
		else
		{
			struct userDataType { T* ptr; } *userdata;

			userdata = (userDataType*)(lua_touserdata(L, index)); 
			
			return userdata->ptr;
		}
	}
}